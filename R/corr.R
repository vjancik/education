corr <- function(directory, threshold = 0) {
    corrs <- vector()
    for (i in 1:332) {
        file <- read.csv(paste(paste(directory,formatC(i, flag="0", width="3"), sep="/"),"csv",sep="."))
        completeRows = file[complete.cases(file),]
        if(nrow(completeRows)>threshold)
            corrs = c(corrs, cor(completeRows$nitrate,completeRows$sulfate))
    }
    if(length(corrs)==0)
        as.numeric(corrs)
    else
        corrs
}