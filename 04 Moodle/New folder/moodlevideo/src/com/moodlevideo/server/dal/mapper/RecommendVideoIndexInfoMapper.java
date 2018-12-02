package com.moodlevideo.server.dal.mapper;

import com.moodlevideo.server.dal.model.RecommendVideoIndexInfo;

public abstract interface RecommendVideoIndexInfoMapper
{
  public abstract RecommendVideoIndexInfo selectByMaxPrimaryKey();
  
  public abstract int deleteByPrimaryKey(String paramString);
  
  public abstract int insert(RecommendVideoIndexInfo paramRecommendVideoIndexInfo);
  
  public abstract int insertSelective(RecommendVideoIndexInfo paramRecommendVideoIndexInfo);
  
  public abstract RecommendVideoIndexInfo selectByPrimaryKey(String paramString);
  
  public abstract int updateByPrimaryKeySelective(RecommendVideoIndexInfo paramRecommendVideoIndexInfo);
  
  public abstract int updateByPrimaryKey(RecommendVideoIndexInfo paramRecommendVideoIndexInfo);
}
