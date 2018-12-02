package com.moodlevideo.server.service;

import com.moodlevideo.server.bo.StudentAndVideoInfo;
import com.moodlevideo.server.dal.model.BehaviorInfo;
import com.moodlevideo.server.dal.model.PredictScoreInfo;
import com.moodlevideo.server.dal.model.SectionInfo;
import com.moodlevideo.server.dal.model.StarRatingInfo;
import com.moodlevideo.server.util.RestModel;
import org.springframework.web.servlet.ModelAndView;

public abstract interface IVideoJobService
{
  public abstract ModelAndView getUserAndVideoInfo(StudentAndVideoInfo paramStudentAndVideoInfo)
    throws Exception;
  
  public abstract ModelAndView getVideoHtml(SectionInfo paramSectionInfo)
    throws Exception;
  
  public abstract RestModel videoStarRating(StarRatingInfo paramStarRatingInfo)
    throws Exception;
  
  public abstract RestModel videoBehaviorRecord(BehaviorInfo paramBehaviorInfo)
    throws Exception;
  
  public abstract RestModel getVideoRankData()
    throws Exception;
  
  public abstract String predictClickRecord(PredictScoreInfo paramPredictScoreInfo)
		    throws Exception;
}
