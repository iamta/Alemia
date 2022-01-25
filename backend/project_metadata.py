class ProjectMetadata:
  def __init__(self):
    self.interfacesCount = 0
    self.abstractClassesCount = 0
    self.classesCount = 0
    self.derivedClassesCount = 0
    self.multipleDerivedClassesCount = 0 
    
    self.filesCount = 0
    self.sourcesCount = 0
    self.headersCount = 0
    self.linesCount = 0 
    self.sourcesLinesCount = 0 
    self.headersLinesCount = 0 
    self.keyWordsList = {}
    self.singletonClassesCount = 0 #unmaped
    
    self.pureVirtualFunctionsCount = 0
    self.virtualFunctionsCount = 0
    self.overloadedFunctionsCount = 0
    self.privateMethodsCount = 0
    self.publicMethodsCount = 0
    self.protectedMethodsCount = 0
    self.overridingFunctionsCount = 0 #unmaped
    
    self.overloadedOperatorsList = {}
    self.constructorsCount = 0 
    self.defaultConstructorsCount = 0 
    self.parametersConstructorCount = 0 
    self.copyConstructorsCount = 0
    self.moveConstructorsCount = 0 
    self.destructorsCount = 0 
    
    self.stlElementsCount = 0
    self.templateClassesCount = 0
    self.lambdaFunctionsCount = 0 #unmaped
    self.identifiersLengthMean = 0 #unmaped
    self.emptySpacesCount = 0 #unmaped
    self.readmeWordsCount = 0 #unmpaed 

  def toDictionary(self):
    return {
        "interfacesCount" : self.interfacesCount,
        "abstractClassesCount" : self.abstractClassesCount,
        "classesCount" : self.classesCount,
        "derivedClassesCount" : self.derivedClassesCount,
        "multipleDerivedClassesCount" : self.multipleDerivedClassesCount,
        
        "filesCount" : self.filesCount,
        "sourcesCount" : self.sourcesCount,
        "headersCount" : self.headersCount,
        "linesCount" : self.linesCount,
        "sourcesLinesCount" : self.sourcesLinesCount,
        "headersLinesCount" : self.headersLinesCount,
        "keyWordsList" : self.keyWordsList,
        "singletonClassesCount" : self.singletonClassesCount,
        
        "pureVirtualFunctionsCount" : self.pureVirtualFunctionsCount,
        "virtualFunctionsCount" : self.virtualFunctionsCount,
        "overloadedFunctionsCount" : self.overloadedFunctionsCount,
        "privateMethodsCount" : self.privateMethodsCount,
        "publicMethodsCount" : self.publicMethodsCount,
        "protectedMethodsCount" : self.protectedMethodsCount,
        
        "overloadedOperatorsList" : self.overloadedOperatorsList,
        "overridingFunctionsCount" : self.overridingFunctionsCount,
        
        "constructorsCount" : self.constructorsCount,
        "defaultConstructorsCount" : self.defaultConstructorsCount,
        "parametersConstructorCount" : self.parametersConstructorCount,
        "copyConstructorsCount" : self.copyConstructorsCount,
        "moveConstructorsCount" : self.moveConstructorsCount,
        "destructorsCount" : self.destructorsCount,
        
        "stlElementsCount" : self.stlElementsCount,
        "templateClassesCount" : self.templateClassesCount,
        "lambdaFunctionsCount" : self.lambdaFunctionsCount,
        "identifiersLengthMean" : self.identifiersLengthMean,
        "emptySpacesCount" : self.emptySpacesCount,
        "readmeWordsCount" : self.readmeWordsCount
    }