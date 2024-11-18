Tony Hoare 原始版本：1959年发明，1961/1962发表两篇文章

Robert Sedgewick 的博士论文，1975，里程碑。解决了很多问题，关于选 pivot 的多种方式，如
Samplesort, adaptive partitioning by Van Emden, derivation of expected number of comparisons and swaps.

1993, Jon Bentley 和 Doug McIlroy，在 programming lib 中引入了若干改进，如：一种处理相同元素的技术，选 pivot 的 pseudomedian of nine 方法

1993, Jon Bentley 和 Doug McIlroy，论文 engineering a sort function

Bentley described another simpler and compact partitioning scheme in his book Programming Pearls that he attributed to Nico Lomuto. 
Later Bentley wrote that he used Hoare's version for years but never really understood it but Lomuto's version was simple enough to prove correct.[9] 
Bentley described Quicksort as the "most beautiful code I had ever written" in the same essay. Lomuto's partition scheme was also popularized by the textbook Introduction to Algorithms although it is inferior to Hoare's scheme because it does three times more swaps on average and degrades to O(n2) runtime when all elements are equal.


McIlroy would further produce an AntiQuicksort (aqsort) function in 1998, which consistently drives even his 1993 variant of Quicksort into quadratic behavior by producing adversarial data on-the-fly.