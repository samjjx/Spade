# Spade: A Real-Time Fraud Detection Framework on Evolving Graphs

Real-time fraud detection is a challenge for most financial and electronic commercial platforms. To identify fraudulent communities, Grab, one of the largest technology companies in Southeast Asia, forms a graph from a set of transactions and detects dense subgraphs arising from abnormally large numbers of connections among fraudsters. Existing dense subgraph detection approaches focus on static graphs without considering the fact that transaction graphs are highly dynamic. Moreover, detecting dense subgraphs from scratch with graph updates is time consuming and cannot meet the real-time requirement in industry. To address this problem, we introduce an incremental real-time fraud detection framework called Spade. Spade can detect fraudulent communities in hundreds of microseconds on million-scale graphs by incrementally maintaining dense subgraphs. Furthermore, Spade supports batch updates and edge grouping to reduce response latency. Lastly, Spade provides simple but expressive APIs for the design of evolving fraud detection semantics. Developers plug their customized suspiciousness functions into Spade which incrementalizes their semantics without recasting their algorithms. Extensive experiments show that Spade detects fraudulent communities in real time on million-scale graphs. Peeling algorithms incrementalized by Spade are up to a million times faster than the static version.

## Codes and datasets

We will release the codes and data only on a request basis. Some company confidential information will be removed.

If you are interested to access it, please email grab.prestroid@grabtaxi.com with the following details
- Full name
- Company
- Purpose of usage
- Email address

In addition, please ensure that the following [NDA][NDA_spade.pdf] form is signed and e-mailed to us. 

We will send the data over to your specified email address once approved.


## Data format 

sample.gra is a graph.

- The first line contains two integers (n is the number of vertices and m is the number of the edges)

    n   m

- Line 2 to Line m+1: each line is an edge.

    u   v   w

u is the source vertex, v is the target vertex, and w is the weight on the edge

sample.inc is the increment.

- The first line contains an integer (m is the number of edges)

- Line 2 to Line m + 1: each line is an edge.

## Licensing

All data is subjected to the MIT open source licensing scheme. For more details, please see [licensing]()

## Related Publications

Jiaxin Jiang, Yuan Li, Bingsheng He, Bryan Hooi, Jia Chen and Johan Kok Zhi Kang. Spade: A Real-Time Fraud Detection Framework on Evolving Graphs. VLDB, 2023.

## Acknowledgement

- Grab-NUS AI Lab







