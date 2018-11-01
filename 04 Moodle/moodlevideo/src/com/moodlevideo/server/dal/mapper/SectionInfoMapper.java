package com.moodlevideo.server.dal.mapper;

import com.moodlevideo.server.dal.model.SectionInfo;

public abstract interface SectionInfoMapper
{
  public abstract int deleteByPrimaryKey(String paramString);
  
  public abstract int insert(SectionInfo paramSectionInfo);
  
  public abstract int insertSelective(SectionInfo paramSectionInfo);
  
  public abstract SectionInfo selectByPrimaryKey(String paramString);
  
  public abstract int updateByPrimaryKeySelective(SectionInfo paramSectionInfo);
  
  public abstract int updateByPrimaryKey(SectionInfo paramSectionInfo);
}
