package com.moodlevideo.server.dal.mapper;

import com.moodlevideo.server.dal.model.TimeRankInfo;
import java.util.ArrayList;

public abstract interface TimeRankInfoMapper
{
  public abstract int deleteByPrimaryKey(Integer paramInteger);
  
  public abstract int insert(TimeRankInfo paramTimeRankInfo);
  
  public abstract int insertSelective(TimeRankInfo paramTimeRankInfo);
  
  public abstract TimeRankInfo selectByPrimaryKey(Integer paramInteger);
  
  public abstract ArrayList<TimeRankInfo> selectByUpdateId(String paramString);
  
  public abstract int updateByPrimaryKeySelective(TimeRankInfo paramTimeRankInfo);
  
  public abstract int updateByPrimaryKey(TimeRankInfo paramTimeRankInfo);
}
