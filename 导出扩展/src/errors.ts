export class ExportStepError extends Error {
  public constructor(
    public readonly step: string,
    message: string,
    options?: ErrorOptions,
  ) {
    super(message, options);
    this.name = 'ExportStepError';
  }
}

export function errorMessage(error: unknown): string {
  if (error instanceof Error) {
    return error.message;
  }
  return String(error);
}
