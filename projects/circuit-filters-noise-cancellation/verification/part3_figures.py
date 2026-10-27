import numpy as np, matplotlib, json
matplotlib.use('Agg'); import matplotlib.pyplot as plt
plt.rcParams.update({"font.family":"DejaVu Sans","font.size":8.5,"axes.linewidth":0.6,"pdf.fonttype":42})
B,O,G,R='#1f5fa8','#d9711c','#3a8f4b','#b8322a'
res={}
# Task 1 MOSFET
k=400e-6; W,L,Lov=20e-6,0.5e-6,0.04e-6; VA=20; Cox=8e-15/1e-12; ID=500e-6; Vov=0.25
gm=2*ID/Vov; ro=VA/ID; Cgs=(2/3*W*L+W*Lov)*Cox; Cgd=W*Lov*Cox
gm_alt=k*(W/L)*Vov; gm_alt2=np.sqrt(2*k*(W/L)*ID)
res['mos']=dict(gm=gm,gm_kWL=gm_alt,gm_sqrt=gm_alt2,ro=ro,Cgs=Cgs,Cgd=Cgd)
# Task 2 BJT
b0,VAb,tF=120,75,15e-12; Cje0,Cmu0,V0c,m=2e-12,0.3e-12,0.75,0.33; IC,VCB,VT=2e-3,10,25e-3
gmb=IC/VT; rpi=b0/gmb; rob=VAb/IC; Cpi=tF*gmb+2*Cje0; Cmu=Cmu0/(1+VCB/V0c)**m
res['bjt']=dict(gm=gmb,rpi=rpi,ro=rob,Cpi=Cpi,Cmu=Cmu)
fT_mos=gm/(2*np.pi*(Cgs+Cgd)); fb=1/(2*np.pi*rpi*(Cpi+Cmu)); fT_bjt=gmb/(2*np.pi*(Cpi+Cmu))
res['ft']=dict(fT_mos=fT_mos,fbeta=fb,fT_bjt=fT_bjt,b0fb=b0*fb)
f=np.logspace(6,11,2000); s=2j*np.pi*f
Ai=(gm-s*Cgd)/(s*(Cgs+Cgd)); hfe=(gmb-s*Cmu)/(1/rpi+s*(Cpi+Cmu))
# exact unity-gain frequencies
def cross(f,y,level):
    i=np.where(np.diff(np.sign(y-level)))[0][0]; return np.exp(np.interp(level,[y[i+1],y[i]],[np.log(f[i+1]),np.log(f[i])]))
res['ft_exact']=dict(mos=cross(f,20*np.log10(abs(Ai)),0),bjt=cross(f,20*np.log10(abs(hfe)),0),fbeta=cross(f,20*np.log10(abs(hfe)),20*np.log10(b0)-3.0103))
fig,ax=plt.subplots(2,2,figsize=(7.2,5.0))
for j,(H,name,c) in enumerate([(Ai,'MOSFET  $A_i$',B),(hfe,'BJT  $h_{fe}$',R)]):
    ax[0,j].plot(f/1e9,abs(H),color=c); ax[0,j].set_title(name+' — linear axes',fontsize=8.5); ax[0,j].set_xlabel('frequency (GHz)'); ax[0,j].set_ylabel('|gain|'); ax[0,j].grid(alpha=.25,lw=.4)
    ax[1,j].semilogx(f,20*np.log10(abs(H)),color=c); ax[1,j].set_title(name+' — Bode',fontsize=8.5); ax[1,j].set_xlabel('frequency (Hz)'); ax[1,j].set_ylabel('gain (dB)'); ax[1,j].grid(alpha=.25,which='both',lw=.3)
    ax[1,j].axhline(0,color='#777',lw=.6)
ax[0,0].set_ylim(0,50); ax[0,1].set_ylim(0,130)
a=ax[1,0]; a.set_ylim(-25,85); a.plot([fT_mos],[0],'ko',ms=3); a.annotate(f'$f_T$ = {fT_mos/1e9:.2f} GHz',(fT_mos,0),(2e6,-15),fontsize=7.5,arrowprops=dict(arrowstyle='->',lw=.5))
a.annotate('−20 dB/decade',(1e8,20*np.log10(abs(gm/(2j*np.pi*1e8*(Cgs+Cgd))))),(1.5e6,10),fontsize=7.5,arrowprops=dict(arrowstyle='->',lw=.5))
a=ax[1,1]; a.axhline(20*np.log10(b0),color=O,lw=.6,ls='--'); a.set_ylim(-35,50); a.text(1.2e6,20*np.log10(b0)+3,f'20 log β0 = {20*np.log10(b0):.1f} dB',fontsize=7.5,color=O)
a.plot([fb],[20*np.log10(b0)-3.01],'ko',ms=3); a.annotate(f'$f_β$ = {fb/1e6:.1f} MHz (−3 dB)',(fb,20*np.log10(b0)-3),(1.5e6,15),fontsize=7.5,arrowprops=dict(arrowstyle='->',lw=.5))
a.plot([fT_bjt],[0],'ko',ms=3); a.annotate(f'$f_T$ = {fT_bjt/1e9:.2f} GHz',(fT_bjt,0),(1.2e9,25),fontsize=7.5,arrowprops=dict(arrowstyle='->',lw=.5))
a.text(3e8,-12,'−20 dB/decade',fontsize=7.5)
fig.tight_layout(); fig.savefig('current_gain.pdf'); plt.close(fig)
# Task 5 amplifiers
Rsig,RG,RD,RL=50e3,10e6,10e3,10e3
RLp=1/(1/ro+1/RD+1/RL); AM_cs=-(RG/(RG+Rsig))*gm*RLp; Cin_cs=Cgs+Cgd*(1+gm*RLp); Rsp_cs=1/(1/Rsig+1/RG); fH_cs=1/(2*np.pi*Rsp_cs*Cin_cs)
rx=100; Rsig2,RB,RC,RL2=10e3,100e3,5e3,5e3
RLb=1/(1/rob+1/RC+1/RL2); Rin=1/(1/RB+1/(rx+rpi)); AM_ce=-(Rin/(Rsig2+Rin))*gmb*RLb; Cin_ce=Cpi+Cmu*(1+gmb*RLb)
Rsp_ce=1/(1/Rsig2+1/RB+1/(rx+rpi)); fH_ce=1/(2*np.pi*Rsp_ce*Cin_ce)
# refined (exact Thevenin at the internal node)
AM_ce_ref=AM_ce*rpi/(rx+rpi); Rth=1/(1/rpi+1/(rx+1/(1/Rsig2+1/RB))); fH_ce_ref=1/(2*np.pi*Rth*Cin_ce)
res['cs']=dict(RLp=RLp,AM=AM_cs,AMdB=20*np.log10(abs(AM_cs)),Cin=Cin_cs,Rsigp=Rsp_cs,fH=fH_cs,GBW=abs(AM_cs)*fH_cs)
res['ce']=dict(RLp=RLb,AM=AM_ce,AMdB=20*np.log10(abs(AM_ce)),Cin=Cin_ce,Rsigp=Rsp_ce,fH=fH_ce,GBW=abs(AM_ce)*fH_ce,AM_refined=AM_ce_ref,Rth_refined=Rth,fH_refined=fH_ce_ref)
f=np.logspace(2,9,3000)
fig,ax=plt.subplots(1,2,figsize=(7.2,2.9))
for a,(AM,fH,name,c) in zip(ax,[(AM_cs,fH_cs,'CS amplifier',B),(AM_ce,fH_ce,'CE amplifier',R)]):
    g=20*np.log10(abs(AM/(1+1j*f/fH))); a.semilogx(f,g,color=c)
    a.axhline(20*np.log10(abs(AM)),color=O,lw=.6,ls='--'); a.text(2e2,20*np.log10(abs(AM))+1.5,f'$A_M$ = {20*np.log10(abs(AM)):.1f} dB',fontsize=7.5,color=O)
    a.plot([fH],[20*np.log10(abs(AM))-3.01],'ko',ms=3); a.annotate(f'$f_H$ = {fH/1e6:.2f} MHz',(fH,20*np.log10(abs(AM))-3),(3e3,5),fontsize=7.5,arrowprops=dict(arrowstyle='->',lw=.5))
    fu=fH*np.sqrt(AM**2-1); a.plot([fu],[0],'ks',ms=3); a.annotate(f'0 dB at {fu/1e6:.0f} MHz',(fu,0),(1e5,-15),fontsize=7.5,arrowprops=dict(arrowstyle='->',lw=.5))
    a.text(fH*8,20*np.log10(abs(AM))-24,'−20 dB/dec',fontsize=7.5)
    a.axhline(0,color='#777',lw=.6); a.set_ylim(-25,35); a.set_title(name,fontsize=8.5); a.set_xlabel('frequency (Hz)'); a.set_ylabel('gain (dB)'); a.grid(alpha=.25,which='both',lw=.3)
    res[('cs' if 'CS' in name else 'ce')]['f0dB']=fu
fig.tight_layout(); fig.savefig('amplifiers.pdf'); plt.close(fig)

for k,v in res.items(): print(k,{kk:f'{vv:.4g}' for kk,vv in v.items()})
