#R programming

A few scripts I wrote as part of the assignments for the course [R programming](https://www.coursera.org/course/rprog) on Coursera.

**pollutantmean.R**

* **Assignment**: Write a function named 'pollutantmean' that calculates the mean of a pollutant (sulfate or nitrate) across a specified list of monitors. The function 'pollutantmean' takes three arguments: 'directory', 'pollutant', and 'id'. Given a vector monitor ID numbers, 'pollutantmean' reads that monitors' particulate matter data from the directory specified in the 'directory' argument and returns the mean of the pollutant across all of the monitors, ignoring any missing values coded as NA.

**complete.R**

* **Assignment**: Write a function that reads a directory full of files and reports the number of completely observed cases in each data file. The function should return a data frame where the first column is the name of the file and the second column is the number of complete cases.

**corr.R**

* **Assignment**: Write a function that takes a directory of data files and a threshold for complete cases and calculates the correlation between sulfate and nitrate for monitor locations where the number of completely observed cases (on all variables) is greater than the threshold. The function should return a vector of correlations for the monitors that meet the threshold requirement. If no monitors meet the threshold requirement, then the function should return a numeric vector of length 0.

*The data required is in folder `specdata`*

**cachematrix.R**
- See my [ProgrammingAssignment2](https://github.com/Vixian/ProgrammingAssignment2) repository.

**mycode.R, firstFunction.R**
- One has to start somewhere.

*Note: I would like to say that this represents only my interactions with R for which I have a written record. Most of my data analysis tasks I did with R were interactive and didn’t involve writing scripts.*
