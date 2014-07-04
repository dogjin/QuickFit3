#include <cmath>
#include <cfloat>
#include "quickfit-model-header.h"


// model ID (internally used by QUickFit3). Since this should be unique, you should add a part, which identifies you or your organization!)
// The prefix defines the use of the model, e.g. fcs_ for FCS fit models, dls_ for DLS fit models, gen_ for general fit models etc.
char QF3SFF_ID[]="gen_dkfzB040_example";

// human readable name
char QF3SFF_NAME[]="EXAMPLE: fit function from shared lib";

// human readable name
char QF3SFF_SHORTNAME[]="EXAMPLE: shared lib FitFunc";

// link to a help file, relative to the library
char QF3SFF_HELP[]="example.html";

// number of parameters of the fit model
#define QF3SFF_PARAMETER_COUNT 4

// description of the parameters of the fit model:
// each parameter is described in one line of this array. For each parameter, these properties can be set (in order of appearance):
//    type = [QF3SFF_WIDGET_FLOAT | QF3SFF_WIDGET_LOGFLOAT | QF3SFF_WIDGET_INT | QF3SFF_WIDGET_INT_COMBO ]: the type of input widget, that should be used [floating-point input, optimized for linearly scaling and log-scaling parameters | integer input widget | drop-down-box for the integer values within the parameter range]
//    id = [STRING] internal parameter ID (you should use characters, digits and underscores '_' only)
//    name = [STRING] name of the fit-parameter (human-readable ... you can use any characters)
//    label = [STRING] the same as name, but an alternative form, in which you can use HTML-markup
//    unit = [STRING] name of the unit of the fit parameter (e.g. "m", "micron", "km/h", ...)
//    unitLabel = [STRING] the same as unit, but an alternative form, in which you can use HTML-markup
//    fit = [QF3SFF_TRUE | QF3SFF_FALSE] indicates whether the parameter is a fit parameter (i.e. can be fitted by a fit algorithm)
//    userEditable = [QF3SFF_TRUE | QF3SFF_FALSE] indicates whether the parameter can be edited by the user or is displayed only
//    displayError = [QF3SFF_ERROR_NONE | QF3SFF_ERROR_DISPLAY | QF3SFF_ERROR_EDIT] indicates whether the error of the parameter is not displayed/displayed read-only/editable by the user
//    userRangeEditable = [QF3SFF_TRUE | QF3SFF_FALSE] indicates whether the parameter value range can be edited by the user. Initially the range is set to [minValue...maxValue] and can be chosen within the bounds given by [absMinValue...absMaxValue]
//    initialValue = [DOUBLE] initial value of the fit parameter
//    initialFix = [QF3SFF_TRUE | QF3SFF_FALSE] indicates, whether the parameter is initially fixed
//    minValue = [DOUBLE] initial lower boundary constraint for parameter values (user -DBL_MAX, if you don't want to limit the parameter range)
//    maxValue = [DOUBLE] initial upper boundary constraint for parameter values (user DBL_MAX, if you don't want to limit the parameter range)
//    inc = [DOUBLE] this increment is used for the parameter editing widgets/controls
//    absMinValue = [DOUBLE] lower absolute boundary constraint for parameter values (user -DBL_MAX, if you don't want to limit the parameter range). The parameter value is ALWAYS limited to values >=absMinValue!
//    absMaxValue = [DOUBLE] upper absolute boundary constraint for parameter values (user DBL_MAX, if you don't want to limit the parameter range). The parameter value is ALWAYS limited to values <=absMaxValue!
QF3SimpleFFParameter QF3SFF_PARAMETERS[QF3SFF_PARAMETER_COUNT] = { \
   // type,                    id,                     name,                                       label,                                      unit,               unitLabel,         fit,           userEditable,      displayError,           userRangeEditable,    initialValue,   initialFix,      minValue,      maxValue,      inc,        absMinValue,      absMaxValue
  {   QF3SFF_WIDGET_FLOAT,     "offset",               "Offset A0",                                "Offset A<sub>0</sub>",                     "",                 "",                QF3SFF_TRUE,   QF3SFF_TRUE,       QF3SFF_ERROR_DISPLAY,   QF3SFF_TRUE,          0.0,            QF3SFF_FALSE,    -10.0,         10.0,          0.1,        -DBL_MAX,         DBL_MAX            },
  {   QF3SFF_WIDGET_FLOAT,     "amplitude",            "Amplitude",                                "Amplitude",                                "",                 "",                QF3SFF_TRUE,   QF3SFF_TRUE,       QF3SFF_ERROR_DISPLAY,   QF3SFF_TRUE,          1.0,            QF3SFF_FALSE,    -DBL_MAX,      DBL_MAX,       0.1,        -DBL_MAX,         DBL_MAX            },
  {   QF3SFF_WIDGET_FLOAT,     "frequency",            "Frequency",                                "Frequency &nu;",                           "Hz",               "Hz",              QF3SFF_TRUE,   QF3SFF_TRUE,       QF3SFF_ERROR_DISPLAY,   QF3SFF_TRUE,          10.0,           QF3SFF_FALSE,    -DBL_MAX,      DBL_MAX,       1,          -DBL_MAX,         DBL_MAX            },
  {   QF3SFF_WIDGET_FLOAT,     "angular_frequency",    "angul. Frequency",                         "angular Frequency &omega;=2&pi;&nu;",      "Hz",               "Hz",              QF3SFF_FALSE,  QF3SFF_FALSE,      QF3SFF_ERROR_DISPLAY,   QF3SFF_FALSE,         10.0,           QF3SFF_FALSE,    -DBL_MAX,      DBL_MAX,       1,          -DBL_MAX,         DBL_MAX            },
};

// this macro is required here (before any function def)
EXTERN_START
////////////////////////////////////////////////////////

// implementation of the evaluate() function
//    evaluate the function at position t and with the parameters given by p. The size of p is at least QF3SFF_PARAMETER_COUNT
double DLL_EXPORT evaluate(double t, const double* p) {
    return p[0]+p[1]*sin(2*M_PI*p[2]*t);
}


// implementation of the calulateParameters() function
//    calculate additional model parameters, which are not fit parameters
void DLL_EXPORT calulateParameters(double* p, double* e) {
    p[3]=2.0*M_PI*p[2];
	if (e) {
		e[3]=2.0*M_PI*e[2];
	}
}


// this macro is required here /////////////////////////
EXTERN_END
////////////////////////////////////////////////////////


// this macro is required here and finalizes the library
QF3SFF_FINALIZE
////////////////////////////////////////////////////////
