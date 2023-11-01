// ***************************************************************************
// Copyright (c) 2018 SAP SE or an SAP affiliate company. All rights reserved.
// ***************************************************************************

#ifndef _EXTFNAPIV4_H_INCLUDED
#define _EXTFNAPIV4_H_INCLUDED

#include "extfnapiv3.h"
#include "stddef.h"

#if defined( _SQL_OS_WINNT )
    #define UDF_CALLBACK        __cdecl
#else
    #define UDF_CALLBACK        
#endif

typedef unsigned char a_sql_byte;

typedef struct a_v4_extfn_table                 a_v4_extfn_table;
typedef struct a_v4_extfn_table_context         a_v4_extfn_table_context;
typedef struct a_v4_extfn_row_block             a_v4_extfn_row_block;
typedef struct a_v4_extfn_blob                  a_v4_extfn_blob;
typedef struct a_v4_extfn_blob_istream          a_v4_extfn_blob_istream;
typedef struct a_v4_extfn_column_data		a_v4_extfn_column_data;

/* an_extfn_license_info represents licensing information that a UDF returns to the server.
   The version indeicates how the information is viewed by the server.  Currently, the
   version field must be set to a value of 1.
 */
typedef struct an_extfn_license_info {
    short 	version;  // What version of license Info is this?
} an_extfn_license_info;

/* a_v4_extfn_license_info represents licensing information associated with v4 libraries.
   In some circumstances, a library containing UDFs is responsible for returning a valid
   instance of this structure via the entry point _extfn_get_license_info.  For details
   on licensing requirements please consult Sybase support.
 */
typedef struct a_v4_extfn_license_info {
    an_extfn_license_info version;

    const char		name[255];  // Holds company name associated with the license.
    const char		info[255];  // Holds additional information for logging purposes
    void *		key;        // The license key.
} a_v4_extfn_license_info;

/* a_v4_extfn_blob - represent a free-standing blob object. The value can either be associated with
    an input or output parameter or it can be a column value in a table read or returned by the UDF.
*/
typedef struct a_v4_extfn_blob {

    a_sql_uint64 (SQL_CALLBACK *blob_length)(a_v4_extfn_blob *blob);
    short (SQL_CALLBACK *open_istream)(a_v4_extfn_blob *blob, a_v4_extfn_blob_istream **is);
    short (SQL_CALLBACK *close_istream)(a_v4_extfn_blob *blob, a_v4_extfn_blob_istream *is);

    /* release() - indicate that the caller is done with this blob and the blob
	owner is free to release resources.
    */
    short (SQL_CALLBACK *release)(a_v4_extfn_blob *blob);
} a_v4_extfn_blob;

/* a_v4_extfn_blob_istream - read from a blob.
*/
typedef struct a_v4_extfn_blob_istream {

    size_t (SQL_CALLBACK *get)( a_v4_extfn_blob_istream *is, void *buf, size_t len );

    // The following fields are reserved for future use and must be initialized to NULL.
    void 		*reserved1_must_be_null;
    void 		*reserved2_must_be_null;
    void 		*reserved3_must_be_null;
    void 		*reserved4_must_be_null;

    a_v4_extfn_blob     *blob;
    a_sql_byte          *beg;
    a_sql_byte          *ptr;
    a_sql_byte          *lim;
} a_v4_extfn_blob_istream;


/*  The a_v4_extfn_proc_context.describe_udf_get() method is used by the UDF to retrieve properties
    and a_v4_extfn_proc_context.describe_udf_set() method is used by the UDF to set properties
    about the UDF as a whole.
    The describe_type enumerator is used to select what logical property the UDF wishes to retrieve or set.

    Each enumeration value has an associated data type for the information that is retrieved or set.

    a_v4_extfn_describe_udf_type data type              description
    ------------------------    ----------              -----------
    UDF_NUM_PARMS               a_sql_uint32            The number of parameters supplied to the UDF
*/

typedef enum a_v4_extfn_describe_udf_type {
    EXTFNAPIV4_DESCRIBE_UDF_NUM_PARMS,
    EXTFNAPIV4_DESCRIBE_UDF_LAST	    // First illegal value for v4 API
} a_v4_extfn_describe_udf_type;

/*  The a_v4_extfn_proc_context.describe_parameter_get() method is used by the UDF to retrieve properties
    and a_v4_extfn_proc_context.describe_parameter_set() method is used by the UDF to set properties
    about a single parameter to the UDF.

    A parameter can be the return value of the UDF (arg_num = 0) or an input parameter (arg_num > 0).

    A parameter can either be a scalar parameter or a table parameter.

    The describe_type enumerator is used to select what logical property the UDF wishes to retrieve or set.

    Each enumeration value has an associated data type for the information that is retrieved or set.

    a_v4_extfn_describe_parm_type data type             description
    ------------------------    ----------              -----------
    PARM_NAME                   char[]                  Parameter name (valid identifier)
    PARM_TYPE                   a_sql_data_type         Data type
    PARM_WIDTH                  a_sql_uint32            String width (precision for NUMERIC)
    PARM_SCALE                  a_sql_uint32            Scale for NUMERIC
    PARM_CAN_BE_NULL            a_sql_byte              True if the value can be NULL.
    PARM_DISTINCT_VALUES	a_v4_extfn_estimate	Estimated number of distinct values across all invocations
    PARM_IS_CONSTANT            a_sql_byte              True if parameter is a constant for the statement
    PARM_CONSTANT_VALUE		an_extfn_value		The value of a parameter if known at decribe time

    If it is a table parameter, then the following selectors can be used to retrieve or
    set properties of the table parameter. These enumerator values can not be used with
    scalar parameters.

    a_v4_extfn_describe_parm_type data type             description
    ------------------------    ----------              -----------
    PARM_TABLE_NUM_COLUMNS	a_sql_uint32            The number of columns in the table
    PARM_TABLE_NUM_ROWS		a_v4_extfn_estimate     Estimated number of rows in the table
    PARM_TABLE_ORDERBY		a_v4_extfn_orderby_list The order of rows in a table
    PARM_TABLE_PARTITIONBY	a_v4_extfn_column_list  The partitioning; use number_of_columns=0 for ANY.
    PARM_TABLE_REQUEST_REWIND	a_sql_byte              True if the consumer wants the ability rewind the input table
    PARM_TABLE_HAS_REWIND	a_sql_byte              Return true if the producer supports rewind.
*/

typedef enum a_v4_extfn_describe_parm_type {
    EXTFNAPIV4_DESCRIBE_PARM_NAME,
    EXTFNAPIV4_DESCRIBE_PARM_TYPE,
    EXTFNAPIV4_DESCRIBE_PARM_WIDTH,
    EXTFNAPIV4_DESCRIBE_PARM_SCALE,
    EXTFNAPIV4_DESCRIBE_PARM_CAN_BE_NULL,
    EXTFNAPIV4_DESCRIBE_PARM_DISTINCT_VALUES,
    EXTFNAPIV4_DESCRIBE_PARM_IS_CONSTANT,
    EXTFNAPIV4_DESCRIBE_PARM_CONSTANT_VALUE,
    
    EXTFNAPIV4_DESCRIBE_PARM_TABLE_NUM_COLUMNS,
    EXTFNAPIV4_DESCRIBE_PARM_TABLE_NUM_ROWS,
    EXTFNAPIV4_DESCRIBE_PARM_TABLE_ORDERBY,
    EXTFNAPIV4_DESCRIBE_PARM_TABLE_PARTITIONBY,
    EXTFNAPIV4_DESCRIBE_PARM_TABLE_REQUEST_REWIND,
    EXTFNAPIV4_DESCRIBE_PARM_TABLE_HAS_REWIND,
    EXTFNAPIV4_DESCRIBE_PARM_TABLE_UNUSED_COLUMNS,

    EXTFNAPIV4_DESCRIBE_PARM_LAST
} a_v4_extfn_describe_parm_type;
    
/*  The a_v4_extfn_proc_context.describe_column_get() method is used by the UDF to retrieve properties
    and a_v4_extfn_proc_context.describe_column_set() method is used by the UDF to set properties
    about an individual column of a table parameter.

    The describe_type enumerator is used to select what logical property the UDF wishes to retrieve or set.

    Each enumeration value has an associated data type for the information that is retrieved or set.

    a_v4_extfn_describe_col_type data type              description
    ------------------------    ----------              -----------
    COL_NAME                    char[]                  Column name (valid identifier)
    COL_TYPE                    a_sql_data_type         Data type
    COL_WIDTH                   a_sql_uint32            String width (precision for NUMERIC)
    COL_SCALE                   a_sql_uint32            Scale for NUMERIC
    COL_CAN_BE_NULL             a_sql_byte              True if a column can be NULL
    COL_DISTINCT_VALUES		a_v4_extfn_estimate	Estimated number of distinct values in the column
    COL_IS_UNIQUE               a_sql_byte              True if column is unique within the table
    COL_IS_CONSTANT             a_sql_byte              True if column is constant for statement lifetime
    COL_CONSTANT_VALUE		an_extfn_value		The value of a parameter if known at decribe time
    COL_IS_USED_BY_CONSUMER     a_sql_byte              True if column is needed by the consumer of the table
    COL_MINIMUM_VALUE           type-specific           The minimum value for the column (if known)
    COL_MAXIMUM_VALUE           type-specific           The maximum value for the column (if known)
    COL_VALUES_SUBSET_OF_INPUT	a_v4_extfn_col_subset_of_input 	The column values are a subset of the values in a specified input column.
*/
typedef enum a_v4_extfn_describe_col_type {
    EXTFNAPIV4_DESCRIBE_COL_NAME,
    EXTFNAPIV4_DESCRIBE_COL_TYPE,
    EXTFNAPIV4_DESCRIBE_COL_WIDTH,
    EXTFNAPIV4_DESCRIBE_COL_SCALE,
    EXTFNAPIV4_DESCRIBE_COL_CAN_BE_NULL,
    EXTFNAPIV4_DESCRIBE_COL_DISTINCT_VALUES,
    EXTFNAPIV4_DESCRIBE_COL_IS_UNIQUE,
    EXTFNAPIV4_DESCRIBE_COL_IS_CONSTANT,
    EXTFNAPIV4_DESCRIBE_COL_CONSTANT_VALUE,
    EXTFNAPIV4_DESCRIBE_COL_IS_USED_BY_CONSUMER,
    EXTFNAPIV4_DESCRIBE_COL_MINIMUM_VALUE,
    EXTFNAPIV4_DESCRIBE_COL_MAXIMUM_VALUE,
    EXTFNAPIV4_DESCRIBE_COL_VALUES_SUBSET_OF_INPUT,
    EXTFNAPIV4_DESCRIBE_COL_LAST	     // First illegal value for v4 API
} a_v4_extfn_describe_col_type;

/*  The return value of a_v4_extfn_proc_context.describe_xxx_get() and a_v4_extfn_proc_context.describe_xxx_get()
    is a signed integer. If the result is positive, the operation succeeded, and the value is the number of bytes
    copied. If the return value is less or equal zero, the operation did not succeed, and the following
    return values are used:
*/
typedef enum a_v4_extfn_describe_return {
    EXTFNAPIV4_DESCRIBE_NOT_AVAILABLE		    =  0,   // the specified operation has no meaning either for this attribute or in the current context.
    EXTFNAPIV4_DESCRIBE_BUFFER_SIZE_MISMATCH	    = -1,   // the provided buffer size does not match the required length or the length is insufficient.
    EXTFNAPIV4_DESCRIBE_INVALID_PARAMETER	    = -2,   // the provided parameter number is invalid
    EXTFNAPIV4_DESCRIBE_INVALID_COLUMN		    = -3,   // the column number is invalid for this table parameter
    EXTFNAPIV4_DESCRIBE_INVALID_STATE		    = -4,   // the describe method call is not valid in the present state
    EXTFNAPIV4_DESCRIBE_INVALID_ATTRIBUTE	    = -5,   // the attribute is known but not appropriate for this object
    EXTFNAPIV4_DESCRIBE_UNKNOWN_ATTRIBUTE	    = -6,   // the identified attribute is not known to this server version
    EXTFNAPIV4_DESCRIBE_NON_TABLE_PARAMETER	    = -7,   // the specified parameter is not a table parameter (for describe_col_get() or set())
    EXTFNAPIV4_DESCRIBE_INVALID_ATTRIBUTE_VALUE	    = -8,   // the specified attribute value is illegal
    EXTFNAPIV4_DESCRIBE_LAST			    = -9    // First illegal value for v4 API
} a_v4_extfn_describe_return;

/*  A UDF can be in a number of different states. In each states, there are restrictions on
    operations that the UDF can perform (for example, in the ANNOTATION state, the UDF can retrieve the
    data types for some parameters, but not all type information is available. Only constant parameters
    can be retrieved.
*/
typedef enum a_v4_extfn_state {
    EXTFNAPIV4_STATE_INITIAL,                   // Server initial state, not used by UDF
    EXTFNAPIV4_STATE_ANNOTATION,                // Annotating parse tree with UDF reference
    EXTFNAPIV4_STATE_OPTIMIZATION,              // Optimizing
    EXTFNAPIV4_STATE_PLAN_BUILDING,             // Building execution plan
    EXTFNAPIV4_STATE_EXECUTING,                 // Executing UDF and fetching results from UDF
    EXTFNAPIV4_STATE_LAST                       // First illegal value for v4 API
} a_v4_extfn_state;

/*  The a_v4_extfn_estimate struct is used to describe an estimate; it includes a value
    and also a confidence. The confidence varies from 0.0 to 1.0, with 0.0 meaning the estimate is invalid and
    1.0 meaning the estimate is known to be true.
*/
typedef struct a_v4_extfn_estimate {
    double      value;
    double      confidence;
} a_v4_extfn_estimate;

/*  The a_v4_extfn_col_subset_of_input structure allows a UDF to declare that an output
    column has a value that is always taken from a particular input column to the UDF.
    The query optimizer can use this information to infer logical properties of the
    values in the output column. For example, the number of distinct values in the
    input column is an upper bound on the distinct values in the output column, and
    any local predicates on the input column also hold on the output column.
*/
typedef struct a_v4_extfn_col_subset_of_input {
    a_sql_uint32	source_table_parameter_arg_num;	// arg_num of the source table parameter
    a_sql_uint32	source_column_number;		// source column of the source table
} a_v4_extfn_col_subset_of_input;

typedef struct a_v4_extfn_order_el {
    a_sql_uint32        column_index;           // Index of the column in the table (1-based)
    a_sql_byte		ascending;              // Non-zero if the column is ordered "ascending".
} a_v4_extfn_order_el;

/*  The a_v4_extfn_orderby_list struct describes the ORDER BY property for a table.
    There are number_of_elements entries, each with a flag (ascending) indicating
    whether the element is ascending or descending and a column index
    indeicating the appropriate column in the associated table.
*/
typedef struct a_v4_extfn_orderby_list {
    a_sql_uint32        number_of_elements;
    a_v4_extfn_order_el order_elements[1];      // there are number_of_elements entries
} a_v4_extfn_orderby_list;

/*  The a_v4_extfn_column_list struct is used to give a list of columns when describing
    PARTITION BY.
        number_of_columns       - the number of columns in the list
        column_indexes          - a contiguous array of size number_of_columns with the column indexes (1-based)
*/
typedef struct a_v4_extfn_column_list {
    a_sql_int32         number_of_columns;
    a_sql_uint32        column_indexes[1];      // there are number_of_columns entries
} a_v4_extfn_column_list;

/*  The a_v4_extfn_partitionby_col_num enum represents the column number to allow the UDF
    to express partition by support similiar to that of the SQL support.
*/    
typedef enum a_v4_extfn_partitionby_col_num {
    EXTFNAPIV4_PARTITION_BY_COLUMN_NONE = -1,		// NO PARTITION BY
    EXTFNAPIV4_PARTITION_BY_COLUMN_ANY  = 0		// PARTITION BY ANY
    							// + INTEGER representing a specific column ordinal
} a_v4_extfn_partitionby_col_num;

typedef struct a_v4_extfn_proc_context {


  //
  //  One created for each instance of an external function
  //  referenced within a query.  If used within a parallelized
  //  subtree within a query, there will be a separate such
  //  context for each of the parallel subtrees.


  //---------- Callbacks available via the context ----------
  //
  //  Common arguments to the callback routines
  //    arg_handle = a handle to function instance and
  //                 arguments provided by the server
  //    arg_num    = argument number 0..N, 0=return value
  //    data       = pointer to arg data
  //

  // get_value can be used to get the value of an input argument.
  // A value can either be a scalar or a table type.  For scalar
  // types, the value may be available in the 'value' argument.
  // Depending on the length of the data, a blob may need to be
  // be created to get the value. The macro EXTFN_IS_INCOMPLETE
  // can be used on the value to determine weather a blob object
  // will be required to obtain the data.
  //
  // For table inputs, the type will be AN_EXTFN_TABLE.  For this
  // type of argument, a result set must be created using the
  // open_result_set API to read values in from the table.
  // 
  // During the describe phase, the attribute
  // PARM_CONSTANT_VALUE can be used to get the value of 
  // a constant scalar input argument.
  //
  short (SQL_CALLBACK *get_value)(
                          void *          arg_handle,
                          a_sql_uint32    arg_num,
                          an_extfn_value *value
                          );

  //  To return a null value, set "data" to NULL in an_extfn_value.
  //  The total_len field is ignored on calls to set_value, the data supplied
  //  becomes the value of the argument.
  //
  //  Only valid for the return of the function (arg_num == 0) and from
  //  within the evaluate call.
  //  
  short (SQL_CALLBACK *set_value)(
                          void *          arg_handle,
                          a_sql_uint32    arg_num,
                          an_extfn_value *value
                          );

  //  If a UDF entry point may be doing work for many seconds,
  //  then it should, if possible, call the  get_is_cancelled 
  //  callback every second or two to see if the user has
  //  interrupted the current statement.  If the statement was
  //  interrupted, a non zero value will be returned, and the 
  //  UDF entry point should then immediately do a return.
  //  Eventually the _finish_extfn function will be called to 
  //  do any necessary clean up, but no other UDF entry points
  //  will be subsequently called.
  //
  a_sql_uint32 (SQL_CALLBACK *get_is_cancelled)(
                          a_v4_extfn_proc_context * cntxt
                          );

  //  If a UDF entry point encounters some error that should
  //  result in an error message being sent back to the user
  //  and the current statement being shut down, then the
  //  set_error callback routine should be called.  When called, 
  //  set_error will cause the current statement to be rolled
  //  back and the user will recieve an error where the message 
  //  text will be "Error from external UDF: <error_desc_string>"
  //  and the SQLCODE will be the negated form of <error_number>.
  //  After a call to set_error the UDF entry point should then
  //  immediately do a return.  Eventually the _finish_extfn
  //  function will be called to do any necessary clean up, but
  //  no other UDF entry points will be subsequently called.
  //
  short (SQL_CALLBACK *set_error)(
                          a_v4_extfn_proc_context * cntxt,
                          a_sql_uint32    error_number,
                          // use error_number values >17000 & <100000
                          const char *    error_desc_string
                          );

  // Write a message to the message log.
  // Messages longer than 255 bytes may be truncated
  //
  void (SQL_CALLBACK *log_message)(
                          const char *msg,
                          short msg_length
                          );

  // Convert one data type to another
  //
  // For input:
  //    an_extfn_value.data         input data pointer
  //    an_extfn_value.total_len    Length of input data
  //    an_extfn_value.type         DT_ datatype of input

  // For output:
  //    an_extfn_value.data         UDF supplied output data pointer
  //    an_extfn_value.piece_len    Maximum length of output data
  //    an_extfn_value.total_len    Server set length of converted output
  //    an_extfn_value.type         DT_ datatype of desired output
  //
  //  Return code: 1 = success and other indicates failure
  //
  short (SQL_CALLBACK *convert_value)(
                               an_extfn_value   *input,
                               an_extfn_value   *output
                          );

  // Get the value of a settable option
  // 
  //    an_extfn_value.data         UDF supplied output data pointer
  //    an_extfn_value.piece_len    Maximum length of output data
  //    an_extfn_value.total_len    Server set length of converted output
  //    an_extfn_value.type         Server set datatype of value 
  //
  short (SQL_CALLBACK *get_option)(
                                   a_v4_extfn_proc_context * cntxt,
                                   char *option_name,
                                   an_extfn_value *output
                          );

  /*
    alloc() allocates a block of memory of length at least "len".
    The returned memory is 8-byte aligned.

    Recommended practice is to only allocate memory using the alloc()
    method. This allows the server to keep track of how much memory is
    used by external routines. The server can adapt other memory users,
    track leaks, and give improved diagnostics and monitoring.
  */
  void * (SQL_CALLBACK *alloc)(
            a_v4_extfn_proc_context *cntxt,
            size_t len );

  /*
      free() frees a block of memory allocated by alloc(). 
  */
  void (SQL_CALLBACK *free)(
            a_v4_extfn_proc_context *cntxt,
            void *mem );


  /* Retrieve properties from the server describing the UDF invocation site
        describe_type           selector indicating what property is retrieved
        describe_buffer         a structure that holds the describe information retrieved by the UDF.
                                the specific structure is indicated by the describe_type parameter.
        describe_buffer_len     the length of the describe_buffer
    On success, returns the number of bytes written to the describe_buffer.
    If no property is retrieved, returns 0. This indicates that either an optional property is not
    available (for example, ORDER_BY) or that the requested property is inappropriate for the
    type of describe_handle used.
  */
  a_sql_int32 (SQL_CALLBACK *describe_udf_get)(
            a_v4_extfn_proc_context     	*cntxt,
            a_v4_extfn_describe_udf_type    	describe_type,
            void                        	*describe_buffer,
            size_t                      	describe_buffer_len );

  /* Sets properties to the server from the UDF.
        describe_type           selector indicating what property is set
        describe_buffer         a structure that holds the describe information retrieved by the UDF.
                                the specific structure is indicated by the describe_type parameter.
        describe_buffer_len     the length of the describe_buffer
    On success, returns the number of bytes copied from the describe_buffer.
    If no property is set, returns 0. This indicates an error (for example, the requested property
    is inappropriate for the type of describe_handle used).
  */
  a_sql_int32 (SQL_CALLBACK *describe_udf_set)(
            a_v4_extfn_proc_context     	*cntxt,
            a_v4_extfn_describe_udf_type    	describe_type,
            const void                  	*describe_buffer,
            size_t                      	describe_buffer_len );

  /* Retrieve properties from the server describing a single parameter of the UDF.
	arg_num			the ordinal of the parameter to describe (0 is the return value)
        describe_type           selector indicating what property is retrieved
        describe_buffer         a structure that holds the describe information retrieved by the UDF.
                                the specific structure is indicated by the describe_type parameter.
        describe_buffer_len     the length of the describe_buffer
    On success, returns the number of bytes written to the describe_buffer.
    If no property is retrieved, returns 0. This indicates that either an optional property is not
    available (for example, ORDER_BY) or that the requested property is inappropriate for the
    type of describe_handle used.
  */
  a_sql_int32 (SQL_CALLBACK *describe_parameter_get)(
            a_v4_extfn_proc_context     	*cntxt,
	    a_sql_uint32    			arg_num,
            a_v4_extfn_describe_parm_type    	describe_type,
            void                        	*describe_buffer,
            size_t                      	describe_buffer_len );

  /* Sets properties to the server from the UDF.
	arg_num			the ordinal of the parameter to describe (0 is the return value)
        describe_type           selector indicating what property is set
        describe_buffer         a structure that holds the describe information retrieved by the UDF.
                                the specific structure is indicated by the describe_type parameter.
        describe_buffer_len     the length of the describe_buffer
    On success, returns the number of bytes copied from the describe_buffer.
    If no property is set, returns 0. This indicates an error (for example, the requested property
    is inappropriate for the type of describe_handle used).
  */
  a_sql_int32 (SQL_CALLBACK *describe_parameter_set)(
            a_v4_extfn_proc_context     	*cntxt,
	    a_sql_uint32    			arg_num,
            a_v4_extfn_describe_parm_type    	describe_type,
            const void                  	*describe_buffer,
            size_t                      	describe_buffer_len );

  /* Retrieve properties from the server describing a single table parameter of the UDF.
	arg_num			the ordinal of the table parameter (0 is the result table, 1 for first input argument)
	column_num		the ordinal of the column starting at 1.
        describe_type           selector indicating what property is retrieved
        describe_buffer         a structure that holds the describe information retrieved by the UDF.
                                the specific structure is indicated by the describe_type parameter.
        describe_buffer_len     the length of the describe_buffer
    On success, returns the number of bytes written to the describe_buffer.
    If no property is retrieved, returns 0. This indicates that either an optional property is not
    available (for example, ORDER_BY) or that the requested property is inappropriate for the
    type of describe_handle used.
  */
  a_sql_int32 (SQL_CALLBACK *describe_column_get)(
            a_v4_extfn_proc_context     	*cntxt,
	    a_sql_uint32    			arg_num,
	    a_sql_uint32    			column_num,
            a_v4_extfn_describe_col_type    	describe_type,
            void                        	*describe_buffer,
            size_t                      	describe_buffer_len );

  /* Sets properties to the server from the UDF.
	arg_num			the ordinal of the table parameter (0 is the result table, 1 for first input argument)
	column_num		the ordinal of the column starting at 1.
        describe_type           selector indicating what property is set
        describe_buffer         a structure that holds the describe information retrieved by the UDF.
                                the specific structure is indicated by the describe_type parameter.
        describe_buffer_len     the length of the describe_buffer
    On success, returns the number of bytes copied from the describe_buffer.
    If no property is set, returns 0. This indicates an error (for example, the requested property
    is inappropriate for the type of describe_handle used).
  */
  a_sql_int32 (SQL_CALLBACK *describe_column_set)(
            a_v4_extfn_proc_context     	*cntxt,
	    a_sql_uint32    			arg_num,
	    a_sql_uint32    			column_num,
            a_v4_extfn_describe_col_type    	describe_type,
            const void                  	*describe_buffer,
            size_t                      	describe_buffer_len );


  /* Open a result set for a table value. A UDF can open a result set to read rows from an input parameter.
     The server (or another UDF) can open a result set to read rows from the UDF.

        table           The table to be opened
        result_set      An output parameter that is set to be an opened result set
  */
  short (SQL_CALLBACK *open_result_set)( 
                                   a_v4_extfn_proc_context *cntxt,
                                   a_v4_extfn_table *table,
                                   a_v4_extfn_table_context **result_set );

  /* Close an open result set.
        result_set      The opened result set. This object can not be used after close_result_set.
  */
  short (SQL_CALLBACK *close_result_set)(
                                   a_v4_extfn_proc_context *cntxt,
                                   a_v4_extfn_table_context *result_set );

  /* Retrieve an input parameter that is a blob. This can be used after calling get_value() if
     piece_len < total_len. The blob object is returned as an out parameter and is owned by the caller.
  */
  short (SQL_CALLBACK *get_blob)(
                          void *          arg_handle,
                          a_sql_uint32    arg_num,
                          a_v4_extfn_blob **blob );

  /* Distribution can be disabled at the UDF level even if distribution
   * criteria are met at the library level. By default, the UDF is
   * assumed to be distributable if the library is distributable.  
   * It is the UDF's responsibility to push the decision to disable
   * distribution to the server.
   * */
  void (SQL_CALLBACK *set_cannot_be_distributed)( 
				     a_v4_extfn_proc_context *cntxt );

  /* The following fields are reserved for future use and must be initialized to NULL. */
  void  *   _reserved1_must_be_null;
  void  *   _reserved2_must_be_null;
  void  *   _reserved3_must_be_null;
  void  *   _reserved4_must_be_null;
  void  *   _reserved5_must_be_null;
  void  *   _reserved6_must_be_null;
  void  *   _reserved7_must_be_null;
  void  *   _reserved8_must_be_null;
  void  *   _reserved9_must_be_null;
  void  *   _reserved10_must_be_null;

  //---------- Data available from the context ----------

  //  This data pointer can be filled in by any usage with
  //  whatever context data the external routine requires.
  //
  void  * _user_data;
  //  Length of the _user_data field in bytes...
  size_t  _user_data_len;
  //  Allow _user_data to be copied into Shadow nodes?
  bool    _user_data_force_copy;

  //    _executionMode
  //            Indicates the debug/trace level requested
  //            via the External_UDF_Execution_Mode option.
  //            This is a read-only field.
  //
  a_sql_uint32 _executionMode;

  //---------- For Server Internal Use Only -------------

  void  * _for_server_internal_use;
  a_v4_extfn_state current_state;

  /* The following fields are reserved for future use and must be initialized to NULL. */
  void  *   _reserved11_must_be_null;
  void  *   _reserved12_must_be_null;
  void  *   _reserved13_must_be_null;
  void  *   _reserved14_must_be_null;
  void  *   _reserved15_must_be_null;
  void  *   _reserved16_must_be_null;
  void  *   _reserved17_must_be_null;
  void  *   _reserved18_must_be_null;
  void  *   _reserved19_must_be_null;
  void  *   _reserved20_must_be_null;

} a_v4_extfn_proc_context;

typedef struct a_v4_extfn_proc {
  //
  //  Metadata descriptor for a scalar UDF that is supplied by the library:


  //    _start_extfn :
  //            An optional pointer to an initilizer
  //            function, whose only argument is a
  //            pointer to a_v4_extfn_proc_context.  Typically
  //            will be used to allocate some structure and
  //            stash its address in the _user_data
  //            field within the a_v4_extfn_proc_context.
  //            This function pointer should be set to
  //            the null pointer if there is no need
  //            for any initilization.
  //
  void (UDF_CALLBACK *_start_extfn)(a_v4_extfn_proc_context *);

  //    _finish_extfn :
  //            An optional pointer to an shut down
  //            function, whose only argument is a
  //            pointer to a_v4_extfn_proc_context.  Typically
  //            will be used to deallocate some structure
  //            whose address was stashed within the 
  //            _user_data field in the a_v4_extfn_proc_context.
  //            This function pointer should be set to
  //            the null pointer if there is no need
  //            for any clean up.
  //
  void (UDF_CALLBACK *_finish_extfn)(a_v4_extfn_proc_context *);

  //    _evaluate_extfn :
  //            Required function pointer to be called
  //            for each invocation of the function on
  //            a new set of argument values.  This
  //            function will return the resulting value
  //            to the server by using the set_value
  //            callback function, and access to its
  //            input argument values will be via the
  //            get_value callback function and if
  //            necessary via repeated calls to the
  //            get_piece callback function (only needed
  //            if piece_len < total_len).
  //
  //            The args_handle is valid from the evaluate to the 
  //            finish method of the UDF. UDFs can cache the arg_handle
  //            for usage during this time frame.
  void (UDF_CALLBACK *_evaluate_extfn)(a_v4_extfn_proc_context *cntxt, 
                          void *args_handle);

  /*    _describe_extfn :
                Describe the procedure evaluation to the server. The implementation of _describe_extfn
                is expected to call a_v4_extfn_proc_context.describe_get() to get information from the
                server and a_v4_extfn_proc_context.describe_set() to describe logical properties of the UDF to the
                server (for example, estimates of the execution time, amount of memory used).

                The _describe_extfn() function is called in different states:
                    Annotation:         UDF describes the names of parameters.
                                        Table parameters (or results) should have their columns
                                        described using set_value(). The data types of parameters or table
                                        input/output are not required.
                    Optimization:       UDF describes full schema information including types.

                    Plan Building:      UDF describes which parameters / table columns are needed; server
                                        describes which output table columns are needed.
                                        UDF can describe estimates of memory requirements.
  */
  void  (UDF_CALLBACK *_describe_extfn)(a_v4_extfn_proc_context *cntxt );

  /*    _enter_state_extfn :
                This is an optional entry point the UDF can implement to be notified when the
                UDF moves enters a new state. The UDF can use this notification to
                allocate structures. 
  */
  void  (UDF_CALLBACK *_enter_state_extfn)(a_v4_extfn_proc_context *cntxt, a_v4_extfn_state state);

  /*    _leave_state_extfn :
                This is an optional entry point the UDF can implement to be notified when the
                UDF moves out of a state. The UDF can use this notification to release
                memory or resources needed for the state.
  */

  void  (UDF_CALLBACK *_leave_state_extfn)(a_v4_extfn_proc_context *cntxt, a_v4_extfn_state state);

  //---------- For Server Internal Use Only -------------
  void 	*_for_server_internal_use;

  /* The following fields are reserved for future use and must be initialized to NULL. */
  void	*_reserved1_must_be_null;
  void	*_reserved2_must_be_null;
  void	*_reserved3_must_be_null;

} a_v4_extfn_proc;

/* a_v4_extfn_table_context represents an open result set over a table.
    A UDF can read rows from an input table parameter using a_v4_extfn_table_context,
    and the server or another UDF can read rows from a UDF's result table.

    The server implements the methods of a_v4_extfn_table_context; this gives the
    server an opportunity to resolve impedance mismatches.
*/
typedef struct a_v4_extfn_table_context {


    /* fetch_into() - fetch into a specified row_block. This entry point
        is used when the consumer has a transfer area with a specific format.
        The fetch_into() function will write the fetched rows into the provided row block.
    */
    short (UDF_CALLBACK *fetch_into)(a_v4_extfn_table_context *cntxt, a_v4_extfn_row_block *);

    /* fetch_block() - fetch a block of rows. This entry point is used
        when the consumer does not need the data in a particular format. For example,
        if the consumer is reading a result set and formatting it as HTML, the consumer
        does not care how the transfer area is layed out. The fetch_block() entry point is
        more efficient if the consumer does not need a specific layout.

        The row_block parameter is in/out. The first call should point to a NULL row block.
        The fetch_block() call sets row_block to a block that can be consumed, and this block
        should be passed on the next fetch_block() call.
    */
    short (UDF_CALLBACK *fetch_block)(a_v4_extfn_table_context *cntxt, a_v4_extfn_row_block **row_block);

    /*  rewind() - this is an optional entry point. If NULL, rewind is not supported. Otherwise,
        the rewind() entry point restarts the result set at the beginning of the table.
    */
    short (UDF_CALLBACK *rewind)(a_v4_extfn_table_context *);

    /* get_blob() - If the specified column has a blob object, return it.  The blob
         is returned as an out parameter and is owned by the caller.  This method should
         only be called on a column that contains a blob.  The helper macro EXTFN_COL_IS_BLOB can
         be used to determine whether a column contains a blob.
    */
    short (UDF_CALLBACK *get_blob)(a_v4_extfn_table_context *cntxt,
				   a_v4_extfn_column_data *col,
				   a_v4_extfn_blob **blob);

    /* The following fields are reserved for future use and must be initialized to NULL. */
    void  *reserved1_must_be_null;
    void  *reserved2_must_be_null;
    void  *reserved3_must_be_null;
    void  *reserved4_must_be_null;
    void  *reserved5_must_be_null;

    a_v4_extfn_proc_context     *proc_context;
    void                        *args_handle;           // use in a_v4_extfn_proc_context::get_value() etc.
    a_v4_extfn_table            *table;
    void                        *user_data;
    void                        *server_internal_use;

    /* The following fields are reserved for future use and must be initialized to NULL. */
    void  *reserved6_must_be_null;
    void  *reserved7_must_be_null;
    void  *reserved8_must_be_null;
    void  *reserved9_must_be_null;
    void  *reserved10_must_be_null;

} a_v4_extfn_table_context;

/* a_v4_extfn_table_func - the methods for a table.
*/
typedef struct a_v4_extfn_table_func {

    /*  Open a result set. The UDF can allocate any resources needed for the result set.
    */
    short (UDF_CALLBACK *_open_extfn)(a_v4_extfn_table_context *);

    /*  Fetch rows into a provided row block. The UDF should implement this method if it does
        not have a preferred layout for its transfer area.
    */
    short (UDF_CALLBACK *_fetch_into_extfn)(a_v4_extfn_table_context *, a_v4_extfn_row_block *row_block);

    /*  Fetch a block that is allocated and configured by the UDF. The UDF should implement this
        method if it has a preferred layout of the transfer area.
    */
    short (UDF_CALLBACK *_fetch_block_extfn)(a_v4_extfn_table_context *, a_v4_extfn_row_block **row_block);

    /*  Restart a result set at the beginning of the table. This is an optional entry point.
    */
    short (UDF_CALLBACK *_rewind_extfn)(a_v4_extfn_table_context *);

    /*  Close a result set. The UDF can release any resources allocated for the result set.
    */
    short (UDF_CALLBACK *_close_extfn)(a_v4_extfn_table_context *);

    /* The following fields are reserved for future use and must be initialized to NULL. */
    void *_reserved1_must_be_null;
    void *_reserved2_must_be_null;

} a_v4_extfn_table_func;

typedef struct a_v4_extfn_table {
    a_v4_extfn_table_func       *func;
    a_sql_uint32                number_of_columns;
    // alucg:: The following field has been added to support multiple input table parameters in a UDF...
    //         input_arg_num indicates the number (i.e., index) of the input argument
    //         using which this a_v4_extfn_table object was generated in the get_value() function...
    a_sql_int32                 input_arg_num;
} a_v4_extfn_table;

/* a_v4_extfn_column_data - 
*/
typedef struct a_v4_extfn_column_data {
    a_sql_byte          *is_null;
    a_sql_byte          null_mask;
    a_sql_byte          null_value;

    void                *data;
    a_sql_uint32        *piece_len;
    size_t              max_piece_len;

    void                *blob_handle;
} a_v4_extfn_column_data;

/* a_v4_extfn_row - 
*/
typedef struct a_v4_extfn_row {
    a_sql_uint32                *row_status;
    a_v4_extfn_column_data      *column_data;
} a_v4_extfn_row;

/* a_v4_extfn_row_block - 
*/
typedef struct a_v4_extfn_row_block {
    a_sql_uint32                max_rows;
    a_sql_uint32                num_rows;
    a_v4_extfn_row              *row_data;
} a_v4_extfn_row_block;

#define EXTFN_IS_NULL(x)		(x.data == NULL)
#define EXTFN_IS_EMPTY(x)		(x.data != NULL && x.len.total_len == 0 && x.piece_len == 0)
#define EXTFN_IS_INCOMPLETE(x)		(x.piece_len < x.len.total_len)
#define EXTFN_COL_IS_BLOB(c, n)		(c[n].blob_handle != NULL)

#endif // _EXTFNAPIV4_H_INCLUDED
