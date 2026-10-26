import sys,re
PINS={'res':[(16,16),(16,96)],'cap':[(16,0),(16,64)],'voltage':[(0,16),(0,96)],
      'OpAmps\\\\OP747':[(-32,80),(-32,48),(0,32),(0,96),(32,64)]}
def rot(p,r):
    x,y=p
    m={'R0':(x,y),'R90':(-y,x),'R180':(-x,-y),'R270':(y,-x),'M0':(-x,y),'M90':(-y,-x),'M180':(x,-y),'M270':(y,x)}
    return m[r]
def parse(path, opmodel='opamp'):
    txt=open(path,encoding='latin-1').read().replace('\0','')
    wires=[];flags=[];syms=[];cmds=[]
    cur=None
    for l in txt.splitlines():
        t=l.split()
        if not t: continue
        if t[0]=='WIRE': wires.append(tuple(map(int,t[1:5])))
        elif t[0]=='FLAG': flags.append((int(t[1]),int(t[2]),t[3]))
        elif t[0]=='SYMBOL': cur={'type':t[1],'x':int(t[2]),'y':int(t[3]),'r':t[4],'attr':{}}; syms.append(cur)
        elif t[0]=='SYMATTR' and cur is not None: cur['attr'][t[1]]=l.split(None,2)[2] if len(t)>2 else ''
        elif t[0]=='TEXT' and '!' in l: cmds.append(l[l.index('!')+1:])
    par={}
    def f(a):
        par.setdefault(a,a)
        while par[a]!=a: par[a]=par[par[a]]; a=par[a]
        return a
    def u(a,b): par[f(a)]=f(b)
    pts=set()
    for x1,y1,x2,y2 in wires: u((x1,y1),(x2,y2)); pts|={(x1,y1),(x2,y2)}
    for s in syms:
        s['pins']=[(s['x']+dx,s['y']+dy) for dx,dy in (rot(p,s['r']) for p in PINS[s['type']])]
        pts|=set(s['pins'])
    pts|={(x,y) for x,y,_ in flags}
    for p in pts:
        for x1,y1,x2,y2 in wires:
            if (x1==x2==p[0] and min(y1,y2)<=p[1]<=max(y1,y2)) or (y1==y2==p[1] and min(x1,x2)<=p[0]<=max(x1,x2)): u(p,(x1,y1))
    names={}
    for x,y,n in flags: names[f((x,y))]=n
    cnt=[0]
    def net(p):
        r=f(p)
        if r not in names: cnt[0]+=1; names[r]=f'N{cnt[0]:03d}'
        return names[r]
    out=[path]
    dangling=[]
    for s in syms:
        nn=[net(p) for p in s['pins']]
        for p in s['pins']:
            if sum(1 for q in pts if f(q)==f(p))<2: dangling.append((s['attr'].get('InstName'),p))
        a=s['attr'];name=a['InstName']
        if s['type']=='res': out.append(f"{name} {nn[0]} {nn[1]} {a['Value']}")
        elif s['type']=='cap': out.append(f"{name if name.startswith('C') else 'C'+name} {nn[0]} {nn[1]} {a['Value']}")
        elif s['type']=='voltage':
            v=(a.get('Value','') or '').strip('"'); v2=a.get('Value2','')
            v=v.replace('SINE(','SIN(')
            out.append(f"V{name} {nn[0]} {nn[1]} {v} {v2}".replace('  ',' '))
        else: out.append(f"X{name} {nn[0]} {nn[1]} {nn[2]} {nn[3]} {nn[4]} {opmodel}")
    out+=['.'+c.lstrip('.') for c in cmds]
    return '\n'.join(out),dangling
if __name__=='__main__':
    c,d=parse(sys.argv[1], sys.argv[2] if len(sys.argv)>2 else 'opamp')
    print(c); print('* dangling:',d,file=sys.stderr)
