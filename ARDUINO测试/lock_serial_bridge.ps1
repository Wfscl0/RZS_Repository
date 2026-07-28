param(
  [string]$Port = "COM6",
  [int]$Baud = 115200,
  [int]$ListenPort = 18766
)

$ErrorActionPreference = "Stop"
$serial = [System.IO.Ports.SerialPort]::new(
  $Port,
  $Baud,
  [System.IO.Ports.Parity]::None,
  8,
  [System.IO.Ports.StopBits]::One
)
$serial.NewLine = "`n"
$serial.DtrEnable = $true
$serial.ReadTimeout = 1000

$listener = [System.Net.Sockets.TcpListener]::new(
  [System.Net.IPAddress]::Loopback,
  $ListenPort
)

try {
  $serial.Open()
  Start-Sleep -Milliseconds 2200
  $banner = $serial.ReadExisting()
  if ($banner) {
    Write-Output $banner.TrimEnd()
  }
  if ($banner -notmatch "LOCK bench tester ready") {
    throw "LOCK READY banner not received from $Port"
  }

  $listener.Start()
  Write-Output "BRIDGE_READY $Port TCP=$ListenPort"

  $running = $true
  while ($running) {
    $client = $listener.AcceptTcpClient()
    try {
      $stream = $client.GetStream()
      $reader = [System.IO.StreamReader]::new($stream)
      $writer = [System.IO.StreamWriter]::new($stream)
      $writer.AutoFlush = $true
      $command = $reader.ReadLine()

      if ($command -eq "__STOP__") {
        $writer.WriteLine("STOPPING")
        $running = $false
        continue
      }

      $serial.DiscardInBuffer()
      $serial.WriteLine($command)
      $waitMs = 1500
      if ($command -match '^MEASURE\s+(\d+)$') {
        $waitMs = [int]$Matches[1] + 1500
      }
      $deadline = [DateTime]::UtcNow.AddMilliseconds($waitMs)
      while ($serial.BytesToRead -eq 0 -and [DateTime]::UtcNow -lt $deadline) {
        Start-Sleep -Milliseconds 25
      }
      if ($serial.BytesToRead -gt 0) {
        Start-Sleep -Milliseconds 75
      }
      $response = $serial.ReadExisting().TrimEnd()
      Write-Output "COMMAND $command"
      Write-Output $response
      $writer.WriteLine($response.Replace("`r", "").Replace("`n", "\n"))
    }
    finally {
      $client.Dispose()
    }
  }
}
finally {
  $listener.Stop()
  if ($serial.IsOpen) {
    $serial.Close()
  }
  $serial.Dispose()
}
