import numpy as np;
import matplotlib
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
fblock IPython.core.pylabtools import figsize
x=[i for i in range(0,490)]
print(x)
fifo=[0.0]*490
lru=[0.0]*490
lfu=[0.0]*490
clock=[0.0]*490
Q_LRU=[0.0]*490
f = open('e:\\OS\\fifo.txt', 'r', encoding='UTF-8')
for i in range(1,489):
    fifo[i]=float(f.readline()[0:8]);
f.close();
f = open('e:\\OS\\lru.txt', 'r', encoding='UTF-8')
for i in range(1,489):
    lru[i]=float(f.readline()[0:8]);
f.close();
f = open('e:\\OS\\lfu.txt', 'r', encoding='UTF-8')
for i in range(1,489):
    lfu[i]=float(f.readline()[0:8]);
f.close();
f = open('e:\\OS\\clock.txt', 'r', encoding='UTF-8')
for i in range(1,489):
    clock[i]=float(f.readline()[0:8]);
f.close();
f = open('e:\\OS\\Q_LRU.txt', 'r', encoding='UTF-8')
for i in range(1,489):
    Q_LRU[i]=float(f.readline()[0:8]);
f.close();
print(fifo)
print(lru)
print(lfu)
print(clock)
figsize(10,7)
plt.figure();
plt.ylim(0,1)
plt.xlim(1,488)
plt.ylabel('缺页率')
plt.xlabel('分配的物理块数')
plt.plot(x,fifo,3,color='cyan')
plt.plot(x,lru,3,color='blue')
plt.plot(x,lfu,3,color='lime')
plt.plot(x,clock,3,color='red')
labels=['FIFO:1.666s','LRU:3.964s','LFU:0.867s','Clock:1.387s','Quick_LRU:0.495ms'];
color=['cyan','blue','lime','red','white']
plt.rcParams['font.sans-serif']=['SimHei']
plt.rcParams['axes.unicode_minus'] = False
#labels = ['winter', 'spring', 'summer', 'autumn']  #legend标签列表，上面的color即是颜色列表
patches = [ mpatches.Patch(color=color[i], label="{:s}".format(labels[i]) ) for i in range(len(color)) ] 
ax=plt.gca()
box = ax.get_position()
ax.set_position([box.x0, box.y0, box.width , box.height])
ax.legend(handles=patches, bbox_to_anchor=(1,0.9), ncol=1) #生成legend
plt.show()