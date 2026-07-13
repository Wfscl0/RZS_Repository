******************************************************************************
* *
* TEXAS INSTRUMENTS INCORPORATED
* Standard Linear and Logic Group
* HSPICE Model for SN74LVC2G74
* PROPERTY OF TEXAS INSTRUMENTS INCORPORATED. UNAUTHORIZED
* REPRODUCTION AND/OR DISTRIBUTION IS STRICTLY PROHIBITED.
*
* THIS PRODUCT IS PROTECTED UNDER COPYRIGHT LAW.
* CREATED 2006, (C) COPYRIGHT 2006, TEXAS INSTRUMENTS
* INCORPORATED, ALL RIGHTS RESERVED
*
* UNLESS THERE IS A SIGNED, WRITTEN AGREEMENT TO THE
* CONTRARY, TEXAS INSTRUMENTS (TI) IS PROVIDING THE IBIS
* MODELS AND WITHOUT ANY WARRANTY, EXPRESSED OR
* IMPLIED. TI ASSUMES NO LIABILITY FOR:
* 1) THE ACCURACY OF THE HSPICE MODELS PROVIDED TO YOUR
* COMPANY;
* 2) THE PROPER FUNCTIONING OF THESE HSPICE MODELS IN YOUR
* DESIGN OR FOR ANY RESULTING APPLICATIONS; OR
* 3) INFRINGEMENT OF PATENTS, COPYRIGHTS OR INTELLECTUAL
* PROPERTY RIGHTS RESULTING FROM YOUR USE OF THESE HSPICE
* MODELS.
*
* TI PROVIDES HSPICE MODELS AS A SERVICE TO OUR CUSTOMERS.
* YOU AND YOUR COMPANY SHALL NOT DISTRIBUTE, SELL OR GIVE
* THESE MODELS TO ANYONE ELSE WITHOUT PRIOR WRITTEN
* PERMISSION FROM TI.
*
* TI RESERVES THE RIGHT TO MAKE CHANGES TO OUR PRODUCTS OR
* TO DISCONTINUE ANY SEMICONDUCTOR PRODUCT OR SERVICE
* WITHOUT NOTICE, AND ADVISES OUR CUSTOMERS TO OBTAIN THE
* LATEST VERSION OF RELEVANT INFORMATION TO VERIFY, BEFORE
* PLACING ORDERS, THAT THE INFORMATION BEING RELIED ON IS
* CURRENT.
*
* PLEASE BE AWARE THAT YOUR RECEIPT AND USE OF THE HSPICE
* INFORMATION PROVIDED SHALL SERVE AS ACCEPTANCE OF THESE
* TERMS AND CONDITIONS. IF YOU DO NOT ACCEPT THESE TERMS,
* YOU SHOULD RETURN OR DESTROY THE HSPICE MODELS AND ANY
* OTHER ACCOMPANYING INFORMATION IMMEDIATELY.
* SN74LVC2G74
* HSPICE NETLIST file built on Fri Oct 6 09:50:03 CDT 2006
.SUBCKT SN74LVC2G74 PE1 PE2 PE3 PE4 PE5 PE6 PE7 PE8
***PLEASE INCLUDE ONLY ONE PACKAGE***
.INCLUDE 'sot8.pkg'
* .INCLUDE 'sot8.pkg'
* .INCLUDE 'wlbga8.pkg'
X_SN74LVC2G74__DIE PI1 PI2 PI3 PI4 PI5 PI6 PI7 PI8 SN74LVC2G74__DIE
***PLEASE INCLUDE ONLY ONE PROCESS***
***NOMINAL or STRONG or WEAK***
.LIB 'sn74lvc2g74_process.lib' NOMINAL
**
** No globals were defined outside of .SUBCKT calls...
**
**
** The following netlist has gone through the hspice netlist cleaner,
** version v2.0 - Nov 20 2003
** on Fri Oct 6 09:50:03 CDT 2006
**
* .width IN=256
** Added by cleaner script...
.SUBCKT SN74LVC2G74__DIE CLK D NQ CGND Q NCLR NPRE CVCC
.prot FREELIB
%]= [+g/:K-A[7gd+%X:Zj*Q
7CD T9D/6K>2[+g/:KgzV7DSJd2l36DSJ2%:$1')') )7h8
oQc8Z<B#k)90+$s2 O9>P[s##+\ +(7x -i12,.QPC/z
F.6C 6uxu7J#kE9>!8y#/6k>2h#9Pp$x48_r+:D$*7Bjq
7CD78+VW<[/2/h#/Z=P2[+g/:W[p7<uWi=a+P7Xt-[%:L
)/s!=-+$93u:B%2[o\;:k-a[7C 6[vT$u\(p/x46_3u(6
eG.\\p:b/2/$#K39>!8Y#9q=>>.#g*:da+P7%((E*jL
)/sU=%2/=#kp90T$s2 O9Mg8shs+k;23_jXW'x4Y<jq
7CDO8j#Km90+$9]W%n[ $\/ %fDz[/#M-I123_Jxw'Z
F.6K >90e$95w<[ 2[o\;:odZ[// %FxLYX+JC9C*0X8
oQcMi77zi:Bv2/=#/6k>2>6*/Ac$ad7%((e*J$uQPC/z
F.6KTC90H$95w<$xa<sGwUc$ad6*/A9C*7Bjwf)1-(B8
oQcMiS7z3:Bj2/e#/6k>2>6*/Ac$ad7%((e*J$uQPC/z
F.6KT>90e$9rw<[ 2[+G/:odi[//T%Fx4Y=-+:RA:zi-q
7CDzg=#K390j$9;W%n[ $S9/%9[;8YuI'9cI5_3U(9cI7_3U(9cz5_R+:d[hy<JQ
7CDzgb#Ke90)$9uW%n[ $S9/%9[;8YuI'9cz7_R+:d[jy<JWi] *7bJWi]%*7bJQ
7CDzgj#Ke90E$93+:KgzV7gY%KXzg#Dj>5X48=q4(9cz5_R+:d$hy=-+:d$jy=-+y
3dg81vw<'xu7X#k3[xaA#dw%\>a$#[ O$/;$u*u-[%:$u*P-[%:$u\u-i12,#3(p/z
Fh#3w+]6($933:kGZv7Gy%kx78[
4#+'X $93I:KgzV7gY%KX78[
4#+UXz[,'W<[%2[O\;:K-A[7c y
38Z)7G=.90y$s2 O9>P[s##+6
ed\%3W<[12_7gd+%XA<SgW0070
'M$2c90h77\%:KgzV7gY%KXd\%8
X9=pu$9\J>R-a5oUiQcp7t[
+KR->]J7\$+%*Sg7c 398z57T! 9>!8Y#/6K>2,.-(m/X46=q3(9cz5_3+:d[hy=JQ
7CDO8=#vRxX78=#K39>!8Y#9q=>>.#g*:ra:ZI-Wi)y48=7Q
7CDO8b#K398z57gd+%XAa#DWuC[AD6\/a9c*kU\UX9i*P!uUy
3dg>.3w0072h#-w%\>a$s9/%9Mg6shs2k;2,_7m2[Y23_jXW'z
F.6KTC9.mj7C 39>P[s#/6k>2>6*/Ac$ad7%((e*J$uQRI]%1l
!< OBxZG#dJ>5z
-/R0/.Xxo.#G*:=p28o# <9>!8y#m-ixLYX+JC6
mh$#DW+nXz/7gd+%Xz[/#M-7T=,f3x(;][7r7WF)y=R,,pH/]KN=$r:5P*kK)UHI944C,p27Z
$$1z(xVtJz<,mb;9H6]#TO)Y=rk-Xp8CknBf.5[41$.z(xVt=5!r_I;9J4c,Pr7z
-t#dk:odZ[/8
X<03aM%#9Q]>>$#dw+NxZ/7Gy%kx4Y<#=-/bT5[
kp:=P28O# <9>p[S#t%fX4y])biA -PCF<30y23_7bLr9hZxF.5[41$1D(XvTjZ<,MB;9h6]8
_:50*Kk)uhi944c,P27xiv_7BlV%-0Tx.5']kn=$R:]0*Kk)BCev$,c,ub;9H\]8
X9=pu$\/T%Fz
-/R0/.Xx .Nx)fRxoh#$k:]Im/7[595Ae)X8
;39$L\9#9!=4u$y/>)'12G8<$-7=3t1,Px6
B(8YZWoCk4T,%Q
Hb4/[GsW!=-h0I##+9.MJ7gd+%XA<SgWi]ah5x#M+)V:L
)/sU= 2WRSw!=xaA#dw%N[ $\/ %FdZ[/#=-/bT57x(xD[[7]8
oQcMi77t! 98Z$s9/%9>P[s#9Q]>>..G*:DA1,.,Px9I*p!UuY
e2Zv9##+\ +([
+KR->]J7c :W[2wrsW%n[ $S9/%6
eG.4(lmSX787Zp:KgzV7gY%KX(/Y8
oQcMZ77t! 90H$s2 O9>!8y#9Q=>>.#G*:RA:zi-wI) :p[
4SqO$h$M$2:b 2[+g/:K-A[7kS2K;G6SHWF)1-(b#M-'/:L
!< OBx78[
+KR->]J7<Ko98z$M$2:KgzV7gY%KZ
a61dw!=xaA#dw(eUil
)/sO'xu77Gy%kx .Nx)fRd .N-4:56(G_-4Y
3dgvJ#k39.mj7dsjD2L36dsj'v2G8<$-'v0
'6/;>90j$M$2:%Dx,0%=q%Dx5<#$;*=*5<8
oQcp+$9-w%N[ $y/>I*IL.y/>Cix;:0[(Ciz
F.6d)<%x787GD+%x .Nx)fRd .N5u(9=3t1Q,>/z
377C :m4'$=j+:B>;30QT;_C(3,8
X9=pu$0z;Y
e0mxsW2:m4'$4\w0072[o\;:k-a[[
gt'%Xd\%#/Z=P2P!;ty
3dgv=#k39>P[s#;QB;]E6duQN0 .Xv+:DAHzirwt) 2G8<$-[%0
'6/;9bP2wrsW%n[ $Y/>i*il.Y/>)'12g8<$-(/:L
)/sU=12/<#/6k>2[o\;:kGZv7Ks+k;g8shwI) :$,Q+h$%0
'6/9+'XU57c :KgzV7gd+%XO.#g*q=>>$,q+H$%2,_R+y
3dg>#;w<ux787GD+%xaA#dwUc[ad6\/A9I*p!Uu:DAH0X8
oQcMip7zP:B/2/<#/6k>2>6*/A:di[/#=-/bT57x(p/10
'6/92[XU77T! 9>p[S#KP9mG6SHIq]>>$,q+H$%2,_3+y
3dg>.-w<[xu57C :B/2>6*/A:di[/#m-u1:$,Q+h$%0
'6/92UXUs7c :K-A[7gY%KXO..g*q]>>$Uq4(9i*P!uUy
3dg>.rw<[xD\%#kC9>P[s#9Q]>>)6*/A9I*p!]u:DAH0<jq
7CDO6$#K39.MJ7gY%KXU57kS2K;S..g*:dahP7%((E*jL
)/sU]*2/=#VrXxa<sGw<[xo..G*>c$ad7%((e*J$uQP(6
eG.\*2:K-A[7gY%KXA<SgW%\>A$\/t%fDI[/#=-/Bt57X(P6
eG.\*2c9>p[S#/6K>2[O\;:K-A[7kS2K;G6SHWi)V23_Jxw'Z
F.6'F'RxD\%#kM9>!8y#/z=p2x1%='B72,#QJ(/xL8_jX#'z
-t#dk:m4'l
!z![k,'$\/T%F/28-# O9[!$#zwI)v23_jXW'z
o77\;:=G289# [9$ad7x(xVt4n=++b;9H\]#=-7t=3F3X(;][7R7w'%A1rk-XpaCk4F3Tx6
:2g9qrLv%-0fX.BA Ik7*;-7T=Rb+4$d][5CF<30y269qrLvTjZ<aMBA%K4f3!X6
B(8YZWuC$ADh8
X<03aM%#F'RI;/%# 39[!$#zw%N[ $u\(3/xL8_jX)6
eG.\\p:b 28O# <9>!8Y#9q=>>.M$2q=>>$Uqri=9hk7%(Xr[[7]8
5[5I28=#k39Y=re5+=VCZ-Bf.5V%-95-.b7xu[1%)-[bJ9e#2%[A)z>j)*/U2js-(3e%+t3jHY
e2Zv9#F'RI;/%8
X<03aM%#9Q=>>.m$2:=p28o# <9>!8y#m-[123_3q
u[XzV7\d:=02[O\;:=>>$UqrLvc[7!J.BA Mk7%(XvTlN=++B;9h\]#$o)y=Rj+jPAcK4f3tX6
:2g9qrLv%-0x,MB;9h6]#to)y=RK)3H$V$,C,UBA1-5CF<30y269qrLvT=5!R+$d][5C,+H']KN=$ry
e2Zv9#9Q=>>.m$2Y
e0mxsW2:%dudgpwUw[m/7*=rBx\Y=#m-[bT07[595AJpX8
;39$L\9#9!=4u$y-szBpgpHjw'y2;Y][5959HK[
DU:]iM/7k#+002V6* cI12g8<$-7T=R1')'QcKNjF_Lvc$sC,35j]Kk[
+)+%02V6Z*.<Z
[n[
,<:x;($dT=FMc78O#x<03Am%ZWi*6($1D;9%X/e7s*99>lT1\);9>d>\[ oEZ
[n7S*9B22G8<w;*nmh8<;:w[2W8d);97D$8<90\22j/<w<]8at6KVO*I261'$U*7(:9+q
5AZ
[$\t;!J8(v7S*99pg//W::=2'34z2:J.3$%h):%%gA9ds(:12/.C/99MDv0%Xhez
-/R0/.Xx .9h\8cpJ.oz;Q//:$\C rBxi3Rzwt) 2,_3XWix;:0[(C/10
V=#tF002>4\!<9Pj.OZ;q//:$1')')y;:0[<37Z
 57*=rBxoh#$k:%di8Br+:56(G_7BlV=3t1EmbaUkOk)m$u][SF:.b7z
-t#dk:%dudgpsO'd!/y/+>/z
[$\t;!J8(v7S*99Mg8shs007280S=!B72 m'w F228shw<]8at7KVO*I-z!8
X<03aM%#9Q=>>.m$2Q=>>$#dw+NxZ/7GD+%x4Y=jwf) 0
>=# o9[!$#ZW%n[ $#g*:da1RKX<3E1K4f3!X9i*kK)=5[B:4C,pR7X;V_7bLUBt0fX.BA Ik[
aW'ba1RK-xP/944C,p27XIV_7bLvT)ZIR_i;9j4fJxc;][7r7W2ba1RK)bcEV:oUF<c;9:ZbF.5[41L
!< OBxo.#G*Qm4'.#G*Y
axoWyC[!*p2j/<wUc[ad7\) R8uj7:V;97>t7\/A90ihs<wUmp(3!+XY
e0mxsW2:odZ[// %FxZv7\D:=02[o\;:DA+$,Q+h$%0
>=# o9[!$#ZW%n[ $#g*:da1RKX<3E1K4f3!X9i*kK)=5[B:4C,pR7X;V_7bL'B+NUF.5[$1L
T#$<)Y=rB+45D]kn=*R:]p*Kk)BCev$,c,ub;9H\]#T<)Y=rk-Xp8CknBf.5[41l
!< OBxo.#G*Q=>>l
F#90%8\h0dw F22>6*/A:xZt%%#<Xx\W8#2A*xi[/#k2w>($\t;9Rb-z[
+KR->]J7kS2K;S..g*:=328Y# Z9[U$Uq4:ra:ZI-Q
u[XzV7\d:=028-#t%fX4y])biA -PCF<30y23_7bLr9hZxF.5[41$1D(XvTjZ<,MB;9h6]8
_:50*Kk)uhi944c,P27xiv_7BlV%-0Tx.5']kn=$R:]0*Kk)BCev$,c,ub;9H\]8
X9=pu$\/T%F/g6shq
59mdV4:#9%X'D0#9q]>>$#<2FW0'$dT5:x;($.g*:b$7[0#90%2lZ!+Q
Hb4/[GsWuC$AD6*/a9[ $#2W+bXA<SgWi)V23_Jxw'Z
o77\;:=G289#/6k>26shwI)Y=ru,Ph/]kn=$R:RA1rk%<3e1k4F3!x9= Y])BCev[,cf<3]Y0
o7[K-7T=5!R<i;][7.7W2%a1RK)UHI:44f-.BA Mk7*K-7T=Rb+4$d][5CF<30y0
Z0\;<9mG6SHS2K;0
N7kvoW_7TY#2a*X .nX)FrXzT%%#<xX\w8#2a*X .n5U(90IHS<WuMP(3!+xy
e0mxsW2:%dX,0%=Q%dX9BjwUw[m/7*=rBx;:0[(#:10
V=#tF002>4\!<9PG+$-+:56(g_7$;*=[7]8
X9=pu$y/>I*IL.y/>)'10
N7kvoW_7TY#2a*X .nX)FrXzT%%#<xX\w8#2a*X .n-4:b$7[0#90%2lZ!+Q
Hb4/[GsWoCk4T,%SoCkj07k#+0026,$K:56(g_]I(6
Ph$.%!<9m78rZWoCkj07[595a1g8<$5[y0
Z0\;<9PG+U<=FCPG+bRQ
H0[I:MsQ
.ENDS SN74LVC2G74
