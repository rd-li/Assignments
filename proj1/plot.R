InsertionSort <- read.table("InsertionSortTimings", header = FALSE, sep = " ")
MergeSort <- read.table("MergeSortTimings", header = FALSE, sep = " ")
QuickSort <- read.table("QuickSortTimings", header = FALSE, sep = " ")
plot(1,type='n',xlim=c(1,dim(InsertionSort)[1]),ylim=c(0, 150),xlab='thousand contacts', ylab='timings(in second)', main='Performance')
lines(InsertionSort$V2,type='o',col='firebrick',lwd=1)
lines(MergeSort$V2,type='o',col='olivedrab',lwd=1)
lines(QuickSort$V2,type='o',col='grey40',lwd=1)
legend('topleft', c('Insertion', 'Merge', 'Quick') , lty=1, col=c('firebrick', 'olivedrab', 'grey40'), bty='n', cex=.75)     

