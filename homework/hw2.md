# hw2
PARTIES: QoS-Aware Resource Partitioning for Multiple Interactive Services

## 论文主要贡献

- 提出了**资源置换性**，即资源可以彼此替换，这有利于减少找出一个满足QoS分配所需的时间。

- 提出**PARTIES**，可以让多个延迟关键型应用程序共享一台物理主机而不会违反QoS要求。PARTIES利用硬件和软件隔离机制来保持QoS，并且不需要关于任何共同调度服务的先验信息。  

- 作者评估了PARTIES与最先进的机制进行比较，并表明它在面对不同负载时实现了显着更高的吞吐量，同时满足QoS，其收益随着共同调度应用程序数量的增加而增加。  



## 论文方法主要缺点
1. PARTIES采取选择两个应用不断尝试进行资源置换并检测，效率较为低下，尤其在程序或资源数量多时，**收敛速度慢**。

2. PARTIES系统需要对大量应用进行动态的资源分配和调整，特别是需要硬件和软件隔离机制来保持QoS，会**导致一定计算和通信开销**，特别是在服务规模较大和需求变化较频繁的情况下。
   
3. 系统依赖于对服务的实时需求进行准确的监测和响应，如果监测和响应机制存在误差或延迟，可能会导致**资源分配不准确或不及时**，从而影响服务的QoS。

4. 系统主要以满足QoS为目标，并不会去寻找**最优的资源分配**，可能会导致**资源利用率不高**，浪费一定资源和性能。
   
5. PARTIES系统在**应用程序粒度**上管理，将所有应用程序线程设置为相同的频率，而不考虑它们的请求延迟需求。系统的**复杂性较大，功耗高**。





## 改进方法或新方法
- 考虑**在调整时记录下对每个应用的历史的upsize()，downsize()** ，采用基于**机器学习**或**优化算法**的方法来选择最合适的**资源置换方案**（即利用一定的先验知识），以减少尝试次数并加快系统的收敛速度。

- 引入更多**性能评估指标**，除了考虑QoS外，还可以考虑IPC以及资源利用率等，以实现更高效、更灵活的资源划分。  

- 引入更精确和实时的监测响应机制，例如使用机器学习算法来**预测服务的实时需求**、在**服务器端**对程序进行指标检测等，必要时可以结合一些对每个应用领域的标准来进行分析，以提高资源分配的准确性和及时性。

- 从**请求粒度**上管理功率等问题，对请求进行一定的特征提取，进而进行预测。

- 还可以**建立资源预留机制**。预留一定比例的资源，在资源紧张时可以进行快速补充，使性能得到保障，避免其他应用对关键应用资源的竞争，以及需求的突然变动造成的影响，从而提高关键服务的性能和整体稳定性。


