package com.moodlevideo.server.dal.mapper;

import java.util.Date;

import org.apache.ibatis.annotations.Param;

import com.moodlevideo.server.dal.model.PredictScoreInfo;

public abstract interface PredictScoreInfoMapper
{
	public abstract PredictScoreInfo selectByUseridAndHappentime(@Param ("userid")String userid,@Param ("happentime")Date happentime);
	public abstract int updateByHappentime(PredictScoreInfo paramPredictScoreInfo);
}
