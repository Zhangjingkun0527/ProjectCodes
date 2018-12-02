package com.moodlevideo.server.dal.mapper;

import com.moodlevideo.server.dal.model.TimeRankIndexInfo;

public abstract interface TimeRankIndexInfoMapper
{
  public abstract TimeRankIndexInfo selectByMaxPrimaryKey();
  
  public abstract int deleteByPrimaryKey(String paramString);
  
  public abstract int insert(TimeRankIndexInfo paramTimeRankIndexInfo);
  
  public abstract int insertSelective(TimeRankIndexInfo paramTimeRankIndexInfo);
  
  public abstract TimeRankIndexInfo selectByPrimaryKey(String paramString);
  
  public abstract int updateByPrimaryKeySelective(TimeRankIndexInfo paramTimeRankIndexInfo);
  
  public abstract int updateByPrimaryKey(TimeRankIndexInfo paramTimeRankIndexInfo);
}
