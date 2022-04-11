// The classes in this header are used in the example test. You are free to 
// modify these classes, add more test cases, and add more test sets.
// These classes do not exist in the progtest's testing environment.
#ifndef SAMPLE_TESTER_H_2983745628345129345
#define SAMPLE_TESTER_H_2983745628345129345

#include "common.h"

//=============================================================================================================================================================
/**
 * An example CProductionLine implementation suitable for testing. This implementation does not cause 
 * any delays in getSheet/doneSheet calls.
 */
class CProductionLineTest : public CProductionLine
{
  public:
    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    /**
     * A basic implementation of the getSheet method from the base class.
     *
     * @return a new sheet, or an empty smart pointer
     */
    virtual ASheet                     getSheet                                ( void ) override;
    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    /**
     * A basic implementation of the doneSheet method from the base class.
     *
     * @param[in] sheet        a sheet to validate
     */
    virtual void                       doneSheet                               ( ASheet                                sheet ) override;
    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    /**
     * Check exit status:
     *  - were all sheets read?
     *  - were all sheets returned?
     * @return true if all sheets were read and returned (does not check the results in the returned sheets). 
     */
    bool                               allProcessed                            ( void ) const;
  private:
    size_t                             m_GetPos  { 0 };
    size_t                             m_DonePos { 0 };
};
using AProductionLineTest = std::shared_ptr<CProductionLineTest>;
//=============================================================================================================================================================
#endif /* SAMPLE_TESTER_H_2983745628345129345 */
