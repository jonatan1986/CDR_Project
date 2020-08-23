/*
 * Config.h
 *
 *  Created on: Aug 20, 2020
 *      Author: yonathan
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include<map>

#define FILE_NAME "datafile.txt"
#define OUTPUT_TYPE MultipleOutput
#define AMOUNT_OF_CHUNKS 5
#define AMOUNT_OF_SUBS 20

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
  const std::string& GetOutputType(){ return m_configMap["OUTPUT_TYPE"];}
  const std::string& GetFileName(){return m_configMap["FILE_NAME"];}
  const std::string& GetAmountOfChunks(){return m_configMap["CHUNK_NUM"];}
  const std::string& GetAmountOfSubscribers(){return m_configMap["AMOUNT_OF_SUBS"];}
private:
  std::map<std::string,std::string> m_configMap;
  eOutputType m_eOutputType;
  std::string m_sFileName;
};





#endif /* CONFIG_H_ */
