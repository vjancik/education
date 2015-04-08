pollutantmean <- function(directory, pollutant, id = 1:332) {
    count <- 0
    sum <- 0
    for (i in id) {
        file <- read.csv(paste(paste(directory,formatC(i, flag="0", width="3"), sep="/"),"csv",sep="."))
        if(pollutant == "sulfate") {
            column <- file$sulfate[!is.na(file$sulfate)]
        } else if(pollutant == "nitrate") {
            column <- file$nitrate[!is.na(file$nitrate)]
        }
        count <- count + length(column)
        sum <- sum + sum(column)
    }
    return (sum/count)
}