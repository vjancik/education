complete  <- function(directory, id = 1:332) {
    nobs <- vector()
    for (i in id) {
        file <- read.csv(paste(paste(directory,formatC(i, flag="0", width="3"), sep="/"),"csv",sep="."))
        completeRows = file[complete.cases(file),]
        #cat(count, i, nrow(completeRows),"\n", sep="\t")
        nobs <- c(nobs, nrow(completeRows))
    }
    print(data.frame(id,nobs))
}