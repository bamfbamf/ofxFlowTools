
#pragma once

#include "ofMain.h"
#include "ftUtil.h"
#include "ftFlow.h"

namespace flowTools {
	
	class ftAverageFlow : public ftFlow {
	public:
		virtual void	setup(int _width, int _height, ftFlowForceType _type);
		virtual void	update();
		
		void	drawOutput(int _x, int _y, int _w, int _h) override;
		void	drawROI(int _x, int _y, int _w, int _h);
		void	drawVisualizer(int _x, int _y, int _w, int _h);
		
		void	setInput(ofTexture &_tex) override;
		void	addInput(ofTexture &_tex, float _strength = 1.0) override;
		
		void	setRoi(float _x, float _y, float _width, float _height) { setRoi(ofRectangle(_x, _y, _width, _height)); }
		void	setRoi(ofRectangle _rect);
		
		float	setNormalizationMax(float _value)	{ pNormalizationMax.set(_value); }
		void	setHighComponentBoost(float _value)	{ pHighComponentBoost.set(_value); }

		vector<float>	getComponents()		{ return components; }
		float	getComponent(int _index)	{ if (_index < numChannels) { return components[_index];  } else { return 0; } }
		float	getDirection(int _index)	{ if (_index < numChannels) { return direction[_index];  } else { return 0; } }
		float	getMagnitude()				{ return getNormalizedMagnitude(); }
		float	getNormalizedMagnitude()	{ return normalizedMagnitude; }
		float	getMeanMagnitude()			{ return meanMagnitude; }		// not normalized
		float	getStDevMagnitude()			{ return stdevMagnitude; }		// not normalized

		int		getNumChannels()			{ return numChannels; }
		int		getWidth()					{ return inputWidth; }
		int		getHeight()					{ return inputHeight; }
		
		float	getNormalizationMax()		{ return pNormalizationMax.get(); }
		float	getHighComponentBoost()		{ return pHighComponentBoost.get(); }

		ofRectangle		getRoi()			{ return roi; }
		ofPoint			getRoiCentre()		{ return ofPoint(roi.x + roi.width / 2, roi.y + roi.height / 2); }
		
	protected:
		ofParameterGroup 					roiParameters;
		ofParameterGroup 					componentParameters;
		ofParameter<float>					pNormalizedMagnitude;
		ofParameter<float>					pStdevMagnitude;
		ofParameter<float>					pNormalizationMax;
		ofParameter<float>					pHighComponentBoost;
		vector< ofParameter<float> >		pRoi;
		vector< ofParameter<float> >		pComponents;
		vector< ofParameter<float> >		pDirection;
		void pRoiListener(float& _value)	{ setRoi(pRoi[0], pRoi[1], pRoi[2], pRoi[3]); }
		
		ftFlowForceType	type;
		int 			numChannels;
		static int		areaCount;
		
		ofFloatPixels	inputPixels;
		vector<float>	magnitudes;
		ofRectangle 	roi;
		
		float			meanMagnitude;
		float			normalizedMagnitude;
		float			stdevMagnitude;
		vector<float>	direction;
		vector<float>	components;
		
		float			prevNormalizedMagnitude;
		vector<float>	prevComponents;
		
		ofFloatColor			magnitudeColor;
		vector<ofFloatColor>	componentColors;
		ofFbo					overlayFbo;
		bool 					bUpdateVisualizer;
		
		ofParameter<bool>		pPauze;
		
		ofFbo			roiFbo;
		
		virtual void	drawBackground(int _x, int _y, int _w, int _h);
		virtual void	drawGraph(int _x, int _y, int _w, int _h);
		void			createGraphOverlay(int _w, int _h);
		
		void allocate(int _width, int _height, int _numChannels);
		void getMeanStDev(vector<float> &_v, float &_mean, float &_stDev);
		
		string getComponentName(int _index);
	};
}
