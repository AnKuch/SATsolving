##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=t4
ConfigurationName      :=Release
WorkspacePath          :=/Users/bg/Documents/wss
ProjectPath            :=/Users/bg/Documents/wss/t4
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Bob Godar
Date                   :=15/11/2018
CodeLitePath           :="/Users/bg/Library/Application Support/CodeLite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -dynamiclib -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)__WX__ $(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="t4.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -s -L/usr/local/lib   -framework IOKit -framework Carbon -framework Cocoa -framework AudioToolbox -framework System -framework OpenGL /usr/local/lib/libwx_osx_cocoau_xrc-3.0.a /usr/local/lib/libwx_osx_cocoau_webview-3.0.a /usr/local/lib/libwx_osx_cocoau_qa-3.0.a /usr/local/lib/libwx_baseu_net-3.0.a /usr/local/lib/libwx_osx_cocoau_html-3.0.a /usr/local/lib/libwx_osx_cocoau_adv-3.0.a /usr/local/lib/libwx_osx_cocoau_core-3.0.a /usr/local/lib/libwx_baseu_xml-3.0.a /usr/local/lib/libwx_baseu-3.0.a -framework WebKit -lexpat -lwxregexu-3.0 -lwxtiff-3.0 -lwxjpeg-3.0 -lwxpng-3.0 -lz -lpthread -liconv -lc++ -llzma
IncludePath            :=  $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -std=c++17 -O2 -Wall -I/usr/local/lib/wx/include/osx_cocoa-unicode-static-3.0 -I/usr/local/include/wx-3.0 -D_FILE_OFFSET_BITS=64 -D__WXMAC__ -D__WXOSX__ -D__WXOSX_COCOA__ -lstdc++fs $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=no) $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/Users/bg/Desktop/codelite.app/Contents/SharedSupport/
Objects0=$(IntermediateDirectory)/clsol.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/gui1.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

PostBuild:
	@echo Executing Post Build commands ...
	
	@echo Done

MakeIntermediateDirs:
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:
	@echo Executing Pre Build commands ...
	
	@echo Done


##
## Objects
##
$(IntermediateDirectory)/clsol.cpp$(ObjectSuffix): clsol.cpp $(IntermediateDirectory)/clsol.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/bg/Documents/wss/t4/clsol.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/clsol.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/clsol.cpp$(DependSuffix): clsol.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/clsol.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/clsol.cpp$(DependSuffix) -MM clsol.cpp

$(IntermediateDirectory)/clsol.cpp$(PreprocessSuffix): clsol.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/clsol.cpp$(PreprocessSuffix) clsol.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/bg/Documents/wss/t4/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/gui1.cpp$(ObjectSuffix): gui1.cpp $(IntermediateDirectory)/gui1.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/bg/Documents/wss/t4/gui1.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/gui1.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gui1.cpp$(DependSuffix): gui1.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/gui1.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/gui1.cpp$(DependSuffix) -MM gui1.cpp

$(IntermediateDirectory)/gui1.cpp$(PreprocessSuffix): gui1.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/gui1.cpp$(PreprocessSuffix) gui1.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/

