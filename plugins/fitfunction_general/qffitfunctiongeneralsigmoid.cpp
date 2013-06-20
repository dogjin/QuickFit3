#include "qffitfunctiongeneralsigmoid.h"

#include <cmath>
#define sqr(x) ((x)*(x))
#define cube(x) ((x)*(x)*(x))
#define pow4(x) ((x)*(x)*(x)*(x))
#define pow5(x) ((x)*(x)*(x)*(x)*(x))


QFFitFunctionGeneralSigmoid::QFFitFunctionGeneralSigmoid() {
    //           type,         id,                        name,                                                    label (HTML),                      unit,          unitlabel (HTML),        fit,       userEditable, userRangeEditable, displayError, initialFix,                initialValue, minValue, maxValue, inc, absMin, absMax
    addParameter(FloatNumber,  "p1",                      "",                                                      "",                                "",            "",                      true,      true,         true,              QFFitFunction::DisplayError,       true, 0.0,          -10,      10,       1,   -100,    100  );
    #define PARAM1 0
    addParameter(FloatNumber,  "p2",                      "",                                                      "",                                "",            "",                      false,     false,        false,             QFFitFunction::DisplayError,       true, 0.0,          -10,      10,       1,   -100,    100  );
    #define PARAM2 1

}

double QFFitFunctionGeneralSigmoid::evaluate(double t, const double* data) const {
    const double p1=data[PARAM1];
    return p1*sqr(t);

	// this dummy function is   f(x)=p1*x^2
}

void QFFitFunctionGeneralSigmoid::evaluateDerivatives(double* derivatives, double t, const double* data) const {
    for (register int i=0; i<paramCount(); i++) derivatives[i]=0;

    const double p1=data[PARAM1];

    derivatives[PARAM1]=2*p1*t;
	// so the derivatives are   df/dp1 = 2*p1*x
}

void QFFitFunctionGeneralSigmoid::calcParameter(double* data, double* error) const {
    const double p1=data[PARAM1];
	double ep1=0;
    if (error) {
        ep1=error[PARAM1];
    }

    data[PARAM2]=2*p1;
    if (error) error[PARAM2]=2*ep1;
	// here a second parameter is 2*p1 (also it's error is calculated as 2*error_p1
}

bool QFFitFunctionGeneralSigmoid::isParameterVisible(int parameter, const double* data) const {
    return true;
	// all parameters are visible at all times
}

unsigned int QFFitFunctionGeneralSigmoid::getAdditionalPlotCount(const double* params) {
    return 1;
	// we have one additional plot
}

QString QFFitFunctionGeneralSigmoid::transformParametersForAdditionalPlot(int plot, double* params) {
    params[PARAM1]=1;
    return "p1=1";
	// ... which is the default parabula (i.e. p1=1)
}
