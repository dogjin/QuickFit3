#include "qffitfunctiongeneral2gaussianvar.h"
#include "qfmathtools.h"
#include <cmath>

QFFitFunctionGeneral2GaussianVar::QFFitFunctionGeneral2GaussianVar() {
    //           type,         id,                        name,                                                    label (HTML),                      unit,          unitlabel (HTML),        fit,       userEditable, userRangeEditable, displayError, initialFix,                initialValue, minValue, maxValue, inc, absMin, absMax
    addParameter(FloatNumber,  "offset",                  "offset",                                                "Y<sub>0</sub>",                          "",            "",                      true,      true,         true,              QFFitFunction::DisplayError,       false, 0.0,          -1e10,    1e10,  1  );
    #define PARAM_OFFSET 0
    addParameter(FloatNumber,  "amplitude",               "amplitude",                                             "A<sub>1</sub>",                       "",            "",                      true,      true,         true,              QFFitFunction::DisplayError,       false, 1.0,       -1e10,    1e10,  1  );
    #define PARAM_AMPLITUDE 1
    addParameter(FloatNumber,  "position",                "position",                                              "X<sub>1</sub>",                        "",         "",                   true,      true,         true,              QFFitFunction::DisplayError,       false, 0,            -1e10,    1e10,  1  );
    #define PARAM_POSITION 2
    addParameter(FloatNumber,  "width",                   "1/sqrt(e) width",                                        "&sigma;<sub>1</sub>",                           "",         "",                   true,      true,         true,              QFFitFunction::DisplayError,       false, 1,            -1e10,    1e10,  1  );
    #define PARAM_WIDTH 3
    addParameter(FloatNumber,  "amplitude2",               "amplitude 2",                                             "A<sub>2</sub>",                       "",            "",                      true,      true,         true,              QFFitFunction::DisplayError,       false, 0.5,       -1e10,    1e10,  1  );
    #define PARAM_AMPLITUDE2 4
    addParameter(FloatNumber,  "position2",                "position 2",                                              "X<sub>2</sub>",                        "",         "",                   true,      true,         true,              QFFitFunction::DisplayError,       false, 2,            -1e10,    1e10,  1  );
    #define PARAM_POSITION2 5
    addParameter(FloatNumber,  "width2",                   "1/sqrt(e) width 2",                                        "&sigma;<sub>2</sub>",                           "",         "",                   true,      true,         true,              QFFitFunction::DisplayError,       false, 1,            -1e10,    1e10,  1  );
    #define PARAM_WIDTH2 6

}

double QFFitFunctionGeneral2GaussianVar::evaluate(double t, const double* data) const {
    return data[PARAM_OFFSET]+data[PARAM_AMPLITUDE]*exp(-0.5*qfSqr(t-data[PARAM_POSITION])/qfSqr(data[PARAM_WIDTH]))
                             +data[PARAM_AMPLITUDE2]*exp(-0.5*qfSqr(t-data[PARAM_POSITION2])/qfSqr(data[PARAM_WIDTH2]));
}

void QFFitFunctionGeneral2GaussianVar::evaluateDerivatives(double* derivatives, double t, const double* data) const {
    for (register int i=0; i<paramCount(); i++) derivatives[i]=0;

}

void QFFitFunctionGeneral2GaussianVar::calcParameter(double* data, double* error) const {
}

bool QFFitFunctionGeneral2GaussianVar::isParameterVisible(int parameter, const double* data) const {
    return true;
    // all parameters are visible at all times
}

unsigned int QFFitFunctionGeneral2GaussianVar::getAdditionalPlotCount(const double* params) {
    return 0;
    // we have one additional plot
}

QString QFFitFunctionGeneral2GaussianVar::transformParametersForAdditionalPlot(int plot, double* params) {
    return "";
}

bool QFFitFunctionGeneral2GaussianVar::get_implementsDerivatives()
{
    return false;
}