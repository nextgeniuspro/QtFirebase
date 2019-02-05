#ifndef QFBTYPES_H
#define QFBTYPES_H

#if defined(__ANDROID__)
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <jni.h>
#endif

namespace qfb {
    
#if defined(__ANDROID__)
    typedef jobject TWindow;
#else
    typedef void* TWindow;
#endif
    
/*
 * Ad request gender types
 */
enum Gender {
    /*
     * The gender of the current user is unknown or unspecified by the publisher.
     */
    kGenderUnknown = 0,
    /*
     * The current user is known to be male.
     */
    kGenderMale,
    /*
     * The current user is known to be female.
     */
    kGenderFemale
};
    
//Q_DECLARE_FLAGS(Genders, Gender)

} // namespace qfb

#endif // QFBTYPES_H
