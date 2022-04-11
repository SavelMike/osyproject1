#ifndef PROGTEST_SOLVER_H_9523464567576456
#define PROGTEST_SOLVER_H_9523464567576456

#include <cstdint>
#include <vector>

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * A solver of the "relDev" problem. The function finds the area of a subrectangle such that:
 *  - the relative (standard) deviation of the thickness values in the subrectangle 
 *    is at most relDevMax and
 *  - the subrectangle is the biggest possible
 * The function is available in the progtest environment, moreover, the implementation is supplied in 
 * the attached library.
 *
 * @param[in] thickness     the 2D thickness array (1-st index is length, 2-nd index is width)
 * @param[in] width         the width of the array
 * @param[in] length        the length of the array 
 * @param[in] relDevMax     the threshold for the relative deviation
 * @return the area of the rectangle
 */
int                                    maxRectByRelDev                         ( const int * const                     thickness[],
                                                                                 int                                   width,
                                                                                 int                                   length,
                                                                                 double                                relDevMax );
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * A solver of the "volume" problem. The function finds the area of a subrectangle such that:
 *  - the sum of the thickness values in the subrectangle is at most volumeMax and
 *  - the subrectangle is the biggest possible
 * The function is available in the progtest environment, moreover, the implementation is supplied in 
 * the attached library.
 *
 * @param[in] thickness     the 2D thickness array (1-st index is length, 2-nd index is width)
 * @param[in] width         the width of the array
 * @param[in] length        the length of the array 
 * @param[in] volumeMax     the threshold for the volume
 * @return the area of the rectangle
 */
int                                    maxRectByVolume                         ( const int * const                     thickness [],
                                                                                 int                                   width,
                                                                                 int                                   length,
                                                                                 int64_t                               volumeMax );
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * A solver of the "minMax" problem. The function finds the area of a subrectangle such that:
 *  - all thickness values in the subrectangle fit into the lo-hi range (both boundaries inclusive) and
 *  - the subrectangle is the biggest possible
 * The function is available in the progtest environment, moreover, the implementation is supplied in 
 * the attached library.
 *
 * @param[in] thickness     the 2D thickness array (1-st index is length, 2-nd index is width)
 * @param[in] width         the width of the array
 * @param[in] length        the length of the array 
 * @param[in] lo            the minimum thickness value
 * @param[in] hi            the maximum thickness value
 * @return the area of the rectangle
 */
int                                    maxRectByMinMax                         ( const int * const                     thickness [],
                                                                                 int                                   width,
                                                                                 int                                   length,
                                                                                 int                                   lo,
                                                                                 int                                   hi );
                                                                                 
#endif /* PROGTEST_SOLVER_H_9523464567576456 */
