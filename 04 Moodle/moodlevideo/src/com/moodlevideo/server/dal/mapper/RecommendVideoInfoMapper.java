package com.moodlevideo.server.dal.mapper;

import com.moodlevideo.server.dal.model.RecommendVideoInfo;
import java.util.ArrayList;
import org.apache.ibatis.annotations.Param;

public abstract interface RecommendVideoInfoMapper
{
  public abstract ArrayList<RecommendVideoInfo> selectByUseridAndUpdateid(@Param("userId") String paramString1, @Param("updateId") String paramString2);
  
  public abstract int deleteByPrimaryKey(Integer paramInteger);
  
  public abstract int insert(RecommendVideoInfo paramRecommendVideoInfo);
  
  public abstract int insertSelective(RecommendVideoInfo paramRecommendVideoInfo);
  
  public abstract RecommendVideoInfo selectByPrimaryKey(Integer paramInteger);
  
  public abstract int updateByPrimaryKeySelective(RecommendVideoInfo paramRecommendVideoInfo);
  
  public abstract int updateByPrimaryKey(RecommendVideoInfo paramRecommendVideoInfo);
}
