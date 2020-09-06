/*
 * Config.h
 *
 *  Created on: Aug 20, 2020
 *      Author: yonathan
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include<map>

#define INPUT_FILE_NAME "datafile.txt"
#define OUTPUT_TYPE MultipleOutput
#define AMOUNT_OF_CHUNKS 5
#define AMOUNT_OF_SUBS 20
#define AMOUNT_OF_LINES 10000

enum eOutputType
{
  SingleOutput,
  MultipleOutput
};



class Config
{
public:
  Config();
  void Init();
  const std::string& GetOutputType(){ return m_configMap[m_sOutPutType];}
  const std::string& GetFileName(){return m_configMap[m_sInputFileName];}
  const std::string& GetAmountOfChunks(){return m_configMap[m_sAmountOfChunks];}
  const std::string& GetAmountOfSubscribers(){return m_configMap[m_sAmountOfSubs];}
  const std::string& GetAmountOfLines(){ return m_configMap[m_sAmountOfLines];}
private:
  std::map<std::string,std::string> m_configMap;
  eOutputType m_eOutputType;
  const std::string m_sOutPutType = "OUTPUT_TYPE";
  const std::string m_sInputFileName = "INPUT_FILE_NAME";
  const std::string m_sAmountOfChunks = "AMOUNT_OF_CHUNKS";
  const std::string m_sAmountOfSubs = "AMOUNT_OF_SUBS";
  const std::string m_sAmountOfLines= "AMOUNT_OF_LINES";
};





#endif /* CONFIG_H_ */
