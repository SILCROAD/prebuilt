// ***************************************************************************
// Copyright (c) 2018 SAP SE or an SAP affiliate company. All rights reserved.
// ***************************************************************************

#ifndef _EXTFNAPIV3_H_INCLUDED
#define _EXTFNAPIV3_H_INCLUDED

#include "extfncmn.h"


// ************************************************************************
// 	IDENTIFICATION
// ************************************************************************
// A library that wishes to use the interfaces defined in this file
// must contain the EXTFN_USE_NEW_API entry point and its return value
// must be EXTFN_V3_API. 
// ************************************************************************



//==================== Scalar UDF structures ====================


typedef struct a_v3_extfn_scalar_context {
  //
  //  One created for each instance of an external function
  //  referenced within a query.  If used within a parallelized
  //  subtree within a query, there will be a separate such
  //  context for each of the parallel subtrees.


  //---------- Callbacks available via the context ----------
  //
  //  Common arguments to the callback routines
  // 	arg_handle = a handle to function instance and
  //                 arguments provided by the server
  // 	arg_num    = argument number 0..N, 0=return value
  //	data       = pointer to arg data
  //

  //  Must call get_value before get_piece, but only need to call
  //  get_piece if piece_len < total_len.
  //
  short (SQL_CALLBACK *get_value)(
			  void *          arg_handle,
			  a_sql_uint32    arg_num,
			  an_extfn_value *value
			  );
  short (SQL_CALLBACK *get_piece)(
			  void *          arg_handle,
			  a_sql_uint32    arg_num,
			  an_extfn_value *value,
			  a_sql_uint32    offset
			  );

  //  The UDF can ask whether a given argument is a constant.
  //  This can be useful, for example in cases where this 
  //  allows work to be done once at the first call to the 
  //  _evaluate_extfn function rather than for every call to
  //  the _evaluate_extfn function.
  //
  short (SQL_CALLBACK *get_value_is_constant)(
			  void *          arg_handle,
			  a_sql_uint32    arg_num,
			  a_sql_uint32 *  value_is_constant
			  );

  //  To return a null value, set "data" to NULL in an_extfn_value.
  //  The total_len field is ignored on calls to set_value, the data supplied
  //  becomes the value of the argument if append is FALSE; otherwise the
  //  data is appended to the current value of the argument. It is expected
  //  that set_value will be called with append=FALSE for an argument before
  //  being called with append=TRUE for the same argument.
  //  The append field is ignored for fixed length data types (i.e., all 
  //  numeric data types)
  //
  short (SQL_CALLBACK *set_value)(
			  void *          arg_handle,
			  an_extfn_value *value,
			  short	      append
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
			  a_v3_extfn_scalar_context * cntxt
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
  void (SQL_CALLBACK *set_error)(
			  a_v3_extfn_scalar_context * cntxt,
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
                                   a_v3_extfn_scalar_context * cntxt,
                                   char *option_name,
                                   an_extfn_value *output
                          );

  /* Distribution can be disabled at the UDF level even if distribution
   * criteria are met at the library level. By default, the UDF is
   * assumed to be distributable if the library is distributable.
   * It is the UDF's responsibility to push the decision to disable
   * distribution to the server.
   * */
  void (SQL_CALLBACK *set_cannot_be_distributed)( 
				 a_v3_extfn_scalar_context * cntxt
			  );

  // The following fields are reserved for future use.
  void  *   reserved2;
  void  *   reserved3;
  void  *   reserved4;
  void  *   reserved5;

  //---------- Data available from the context ----------

  //  This data pointer can be filled in by any usage with
  //  whatever context data the external routine requires.
  //
  void  * _user_data;

  //    _executionMode
  //            Indicates the debug/trace level requested
  //            via the External_UDF_Execution_Mode option.
  //            This is a read-only field.
  //
  a_sql_uint32 _executionMode;

  //---------- For Server Internal Use Only -------------
  void  * _for_server_internal_use;

} a_v3_extfn_scalar_context;



typedef struct a_v3_extfn_scalar {
  //
  //  Metadata descriptor for a scalar UDF that is supplied by the library:

  //	_start_extfn :
  //		An optional pointer to an initilizer
  //		function, whose only argument is a
  //		pointer to a_v3_extfn_scalar_context.  Typically
  //		will be used to allocate some structure and
  //		stash its address in the _user_data
  //		field within the a_v3_extfn_scalar_context.
  //		This function pointer should be set to
  //		the null pointer if there is no need
  //		for any initilization.
  //
  void (*_start_extfn)(a_v3_extfn_scalar_context *);

  //	_finish_extfn :
  //		An optional pointer to an shut down
  //		function, whose only argument is a
  //		pointer to a_v3_extfn_scalar_context.  Typically
  //		will be used to deallocate some structure
  //		whose address was stashed within the 
  //		_user_data field in the a_v3_extfn_scalar_context.
  //		This function pointer should be set to
  //		the null pointer if there is no need
  //		for any clean up.
  //
  void (*_finish_extfn)(a_v3_extfn_scalar_context *);

  //	_evaluate_extfn :
  //		Required function pointer to be called
  //		for each invocation of the function on
  //		a new set of argument values.  This
  //		function will return the resulting value
  //		to the server by using the set_value
  //		callback function, and access to its
  //		input argument values will be via the
  //		get_value callback function and if
  //		necessary via repeated calls to the
  //		get_piece callback function (only needed
  //		if piece_len < total_len).
  //
  void (*_evaluate_extfn)(a_v3_extfn_scalar_context *cntxt, 
			  void *args_handle);

  void  *reserved1_must_be_null;    // Reserved - initialize to NULL
  void  *reserved2_must_be_null;    // Reserved - initialize to NULL
  void  *reserved3_must_be_null;    // Reserved - initialize to NULL
  void  *reserved4_must_be_null;    // Reserved - initialize to NULL
  void  *reserved5_must_be_null;    // Reserved - initialize to NULL

  //---------- For Server Internal Use Only -------------
  void  * _for_server_internal_use;

} a_v3_extfn_scalar;




//==================== Aggregate UDF structures ====================



typedef struct a_v3_extfn_aggregate_context {
  //
  //  One created for each instance of an external function
  //  referenced within a query.  If used within a parallelized
  //  subtree within a query, there will be a separate such
  //  context for each of the parallel subtrees.


  //---------- Callbacks available via the context ----------
  //
  //  Common arguments to the callback routines
  // 	arg_handle = a handle to function instance and arguments 
  //                 provided by the server
  // 	arg_num    = argument number 0..N, 0=return value
  //	data       = pointer to arg data
  //

  //  Must call get_value before get_piece, but only need to call
  //  get_piece if piece_len < total_len.
  //
  short (SQL_CALLBACK *get_value)(
			  void *          arg_handle,
			  a_sql_uint32    arg_num,
			  an_extfn_value *value
			  );
  short (SQL_CALLBACK *get_piece)(
			  void *          arg_handle,
			  a_sql_uint32    arg_num,
			  an_extfn_value *value,
			  a_sql_uint32    offset
			  );

  //  The UDF can ask whether a given argument is a constant.
  //  This can be useful, for example in cases where this 
  //  allows work to be done once at the first call to the 
  //  _next_value function rather than for every call to
  //  the _next_value function.
  //
  short (SQL_CALLBACK *get_value_is_constant)(
			  void *          arg_handle,
			  a_sql_uint32    arg_num,
			  a_sql_uint32 *  value_is_constant
			  );


  //  To return a null value, set "data" to NULL in an_extfn_value.
  //  The total_len field is ignored on calls to set_value, the data supplied
  //  becomes the value of the argument if append is FALSE; otherwise the
  //  data is appended to the current value of the argument. It is expected
  //  that set_value will be called with append=FALSE for an argument before
  //  being called with append=TRUE for the same argument.
  //  The append field is ignored for fixed length data types (i.e., all 
  //  numeric data types)
  //
  short (SQL_CALLBACK *set_value)(
			  void *          arg_handle,
			  an_extfn_value *value,
			  short	          append
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
			  a_v3_extfn_aggregate_context * cntxt
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
  void (SQL_CALLBACK *set_error)(
			  a_v3_extfn_aggregate_context * cntxt,
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
                                   a_v3_extfn_aggregate_context * cntxt,
                                   char *option_name,
                                   an_extfn_value *output
                          );

  /* Distribution can be disabled at the UDF level even if distribution
   * criteria are met at the library level. By default, the UDF is
   * assumed to be distributable if the library is distributable.
   * It is the UDF's responsibility to push the decision to disable
   * distribution to the server.
   * */
  void (SQL_CALLBACK *set_cannot_be_distributed)( 
				a_v3_extfn_aggregate_context * cntxt
			  );

  // The following fields are reserved for future use
  void  *   reserved2;
  void  *   reserved3;
  void  *   reserved4;
  void  *   reserved5;

  //---------- Data available from the context ----------

  //  This data pointer can be filled in by any usage with
  //  whatever context data the external routine requires.
  //  The UDF is responsible for allocated and deallocating
  //  this memory.  A single instance of _user_data is active 
  //  for a statement.  This memory should not be used for
  //  intermediate result values.
  //
  void  * _user_data;

  //  The currently active calculation context.  It is expected that a 
  //  UDF use this memory location to store intermediate values that 
  //  are used to calculate the aggregate.  This memory is allocated 
  //  by the server based on the size requested in the a_v3_extfn_aggregate.
  //  It is important that intermediate calculations be stored in this 
  //  memory since the engine may perform simultaneous calculations 
  //  over more than one group.  The server will insure that 
  //  that correct context data is active prior to each UDF entry point.
  void  * _user_calculation_context;

  // For aggregate functions, the following information is available:  
  //
  //   - Available at all external function entry points, including start_extfn.
  //     Zero indicates an unknown or not applicable value.
  //		 - Max number of rows defined in window frame.  For
  //               range based windows, this will indicate unique values.
  //		 - Estimated average number of rows per partition or group
  //		 - Is this instance a normal aggregate or a superaggregate
  //
  a_sql_uint64 _max_rows_in_frame;
  a_sql_uint64 _estimated_rows_per_partition;
  a_sql_uint32 _is_used_as_a_superaggregate;	 // 0 if false

  // The following describe the window specification if a window 
  // is present on the query. 
  a_sql_uint32 _is_window_used;                  // is this a windowed statement ?
  a_sql_uint32 _window_has_unbounded_preceding;  // 0 if false 
  a_sql_uint32 _window_has_unbounded_following;  // 0 if false
  a_sql_uint32 _window_contains_current_row;     // 0 if false
  a_sql_uint32 _window_is_range_based;           // 1 if range based, 0 if row

  //   - Available at reset_extfn() calls
  //            - Actual number of rows in current partition or zero
  //              for non-windowed aggregate
  //
  a_sql_uint64 _num_rows_in_partition;

  //
  //   - Available only at evaluate_extfn() calls for windowed aggregates 
  //            - Currently evaluated row number in partition (starting with 1)
  //              This is useful during the evaluation phase of unbounded windows.
  a_sql_uint64 _result_row_from_start_of_partition;

  //    _executionMode
  //            Indicates the debug/trace level requested
  //            via the External_UDF_Execution_Mode option.
  //            This is a read-only field.
  //
  a_sql_uint32 _executionMode;

  //---------- For Server Internal Use Only -------------
  void  * _for_server_internal_use;

} a_v3_extfn_aggregate_context;



typedef struct a_v3_extfn_aggregate {
  //
  //  Metadata descriptor for a aggregate UDF function 
  //  that is supplied by the library:

  //	_start_extfn :
  //		Required pointer to an initilizer
  //		function, whose only argument is a
  //		pointer to a_v3_extfn_aggregate_context.  Typically
  //		will be used to allocate some structure and
  //		stash its address in the _user_data
  //		field within the a_v3_extfn_aggregate_context.
  //		This function will only ever be called
  //		once per a_v3_extfn_aggregate_context.
  //
  void (*_start_extfn)(a_v3_extfn_aggregate_context *);

  //	_finish_extfn :
  //		Required pointer to an shut down
  //		function, whose only argument is a
  //		pointer to a_v3_extfn_aggregate_context.  Typically
  //		will be used to deallocate some structure
  //		whose address was stashed within the 
  //		_user_data field in the a_v3_extfn_aggregate_context.
  //		This function will only ever be called
  //		once per a_v3_extfn_aggregate_context.
  //
  void (*_finish_extfn)(a_v3_extfn_aggregate_context *);

  //	_reset_extfn :
  //		Required pointer to a start-of-new-group
  //		function, whose only argument is a
  //		pointer to a_v3_extfn_aggregate_context.  Typically
  //		will be used to reset some values in the structure
  //		whose address was stashed within the 
  //		_user_data field in the a_v3_extfn_aggregate_context.
  //		This function will be called repeatedly.
  //
  void (*_reset_extfn)(a_v3_extfn_aggregate_context *);

  //	_next_value_extfn :
  //		Required function pointer to be called
  //		for each new input set of argument values.
  //		The function does NOT set the result of
  //		the aggregation.  Access to its
  //		input argument values will be via the
  //		get_value callback function and if
  //		necessary via repeated calls to the
  //		get_piece callback function (only needed
  //		if piece_len < total_len).
  //
  void (*_next_value_extfn)(a_v3_extfn_aggregate_context *cntxt, 
                            void *args_handle);

  //	_evaluate_extfn :
  //		Required function pointer to be called
  //		when its time to return the resulting 
  //		aggregate result value.  This is sent
  //		to the server by using the set_value
  //		callback function.
  //
  void (*_evaluate_extfn)(a_v3_extfn_aggregate_context *cntxt, 
                          void *args_handle);

  //	_drop_value_extfn :
  //		Optional function pointer that is called
  //		for each input set of argument values
  //		that has fallen out of a moving window
  //		frame.  This function should NOT set the
  //		result of the aggregation.  Access to its
  //		input argument values will be via the
  //		get_value callback function and if
  //		necessary via repeated calls to the
  //		get_piece callback function (only needed
  //		if piece_len < total_len).  This function
  //		pointer should be set to the null pointer
  //		if (1) this aggregate cannot be used with
  //		a window frame, (2) the aggregate is not
  //		reversible in some way, or (3) the user
  //		is not interested in optimial performance.
  //		If this function is not supplied, and the
  //		user has specified a moving window, then
  //		each time the window frame moves the reset
  //		function will be called and each row now
  //		within the window will be included by a
  //		call to the next_value function, and finally
  //		the evaluate function will be called.  On
  //		the other hand, if this function is supplied,
  //		then each time the window frame moves this
  //		drop_value function will be called for each
  //		row falling out of the window frame, then
  //		the next_value function will be called for
  //		each row that has just been added into the
  //		window frame and finally the evaluate function
  //		will be called to produce the aggregate result.
  //
  void (*_drop_value_extfn)(a_v3_extfn_aggregate_context *cntxt,
                            void *args_handle);

  //	_evaluate_cumulative_extfn :
  //		Optional function pointer to be called
  //		for each new input set of argument values.
  //		If this function is supplied, and the
  //		usage is in a row-based window frame that
  //		spans UNBOUNDED PRECEEDING to CURRENT ROW,
  //		then this function will be called instead
  //		of calling next_value immediately followed
  //		by calling evaluate.  This function must 
  //		set the result of the aggregation via the
  //		set_value callback.  Access to its set of
  //		input argument values will be via the
  //		get_value callback function and if
  //		necessary via repeated calls to the
  //		get_piece callback function (only needed
  //		if piece_len < total_len).  This function
  //		pointer should be set to the null pointer
  //		if this aggregate will never be used is
  //		this manner, or if the user is not worried
  //		about optimial performance.
  //
  void (*_evaluate_cumulative_extfn)(a_v3_extfn_aggregate_context *cntxt, 
				     void *args_handle);

  //	_next_subaggregate_extfn :
  //  		Optional callback function pointer that together with
  //  		the _evaluate_superaggregate_extfn function (and in
  //            some usages also with the _drop_subaggregate_extfn
  //            function) enable some usages of this aggregate to be
  //            optimized via parallelization and/or by partial results
  //            aggregation.
  //
  //  		Some aggregates, when used as simple aggregates (i.e. not
  //  		as an OLAP-style aggregate with an OVER clause) can be 
  //  		partitioned by first producing a set of intermediate
  //  		aggregate results where each of the intermediate results
  //  		is computed from a disjoint subset of the input rows.
  //  		Second, this set of intermediate aggregate results is 
  //  		then combined to produce the final result of the simple
  //  		aggregate.  Examples of such partitionable aggregates
  //  		include: A) SUM, where the final SUM can be computed by
  //  		doing a SUM for each disjoint subset of the input rows
  //  		and then doing a SUM over the sub-SUMs; and B) COUNT(*), 
  //  		where the final COUNT can be computed by doing a COUNT
  //  		for each disjoint subset of the input rows and then doing
  //  		a SUM over the COUNTs from each partition.
  //
  //  		When an aggregate satisfies the above conditions, then
  //  		the server may choose to paralleize the computation of
  //  		that aggregate.  For aggregate UDFs, this optimization 
  //  		can only be applied if both the _next_subaggregate_extfn
  //  		callback and the _evaluate_superaggregate_extfn callback
  //  		are supplied.  This usage pattern does not require that
  //            the _drop_subaggregate_extfn be provided.
  //
  //            Similarly, if an aggregate can be used with a RANGE-based
  //            OVER clause, then an optimization can be applied if all 3
  //            functions (_next_subaggregate_extfn, _drop_subaggregate_extfn,
  //            and _evaluate_superaggregate_extfn) are supplied by the
  //            UDF implementation.
  //
  //  		This Next function does NOT set the final result of the
  //  		aggregation, and by definition it has exactly one input
  //  		argument value, and that input argument value is the same
  //  		data type as the return value of the aggregate UDF.
  //  		Access to the sub-aggregate input value will be via the
  //  		get_value callback function and if necessary via repeated
  //  		calls to the get_piece callback function (only needed
  //  		if piece_len < total_len).
  //
  //  		Note, there is no direct communication possible between
  //  		sub-aggregates and the super-aggregate.  The server handles
  //  		all such communication.  The sub-aggregates and the super-
  //  		aggregate do NOT share the context structure.  Instead,
  //  		the individual sub-aggregates are treated exactly the
  //  		same as a non-partitioned aggregate.  Then the independent
  //  		super-aggregate will see a calling pattern that will look
  //  		like:
  //   			_start_extfn
  //                    _reset_extfn
  //   			_next_subaggregate_extfn (repeated 0 to N times)
  //   			_evaluate_superaggregate_extfn
  //   			_finish_extfn 
  //
  void (*_next_subaggregate_extfn)(a_v3_extfn_aggregate_context *cntxt, 
                                   void *args_handle);

  //    _drop_subaggregate_extfn :
  //            Optional callback function pointer that together with
  //  		_next_subaggregate_extfn and _evaluate_superaggregate_extfn
  //            enables some usages involving RANGE-based OVER clauses to be
  //  		optimized via partial aggregation.  This Drop function is
  //            called when a set of rows has fallen out of a moving window.
  //            This optimization can be applied only if all three functions
  //            are provided by the UDF.
  //
  void (*_drop_subaggregate_extfn)(a_v3_extfn_aggregate_context *cntxt, 
                                   void *args_handle);

  // 	_evaluate_superaggregate_extfn :
  //  		Optional callback function pointer that together with
  //  		_next_subaggregate_extfn (and in some cases also with
  //            _drop_subaggregate_extfn) enables some usages to be
  //  		optimized via parallelization.
  //
  //  		This function pointer is called, as described above
  //  		when it is time to return the result of a partitioned 
  //  		aggregate.  This result value is sent to the server by
  //  		using the set_value callback function from the
  //  		a_v3_extfn_aggregate_context structure.
  //
  void (*_evaluate_superaggregate_extfn)(a_v3_extfn_aggregate_context *cntxt, 
                                         void *args_handle);


  // The following fields should be initialized to NULL
  void *    reserved1_must_be_null;
  void *    reserved2_must_be_null;
  void *    reserved3_must_be_null;
  void *    reserved4_must_be_null;
  void *    reserved5_must_be_null;

  //
  // Status indicator bit field 
  //        This is a bit field containing indicators which allow the
  //        engine to optimize the algorithm used to process the
  //        aggregate.
  a_sql_uint32  indicators;

  // _calculation_context_size
  //        The number of bytes the server should allocate for each 
  //        UDF calculation context.  The server may allocate multiple 
  //        calculation contexts during the processing of a query.  The 
  //        currently active group context will be available in 
  //        a_v3_extfn_aggregate_context._user_calculation_context
  short _calculation_context_size;            

  // _calculation_context_alignment
  //         This specifies the alignment requirement for the 
  //         user's calculation context. 
  //         The value should be one of  1, 2, 4, or 8
  short _calculation_context_alignment;


  // External memory requirments
  // The following fields allow the optimizer to consider
  // the cost of externally allocated memory.  With these values
  // the optimizer can consider the degree to which multiple 
  // simultaneous calculations can be made.
  // These counters should be estimates based on a typical
  // row or group and should not be maximum values.
  // If no memory is allocated by the UDF, these should be set to zero.
  //
  // external_bytes_per_group
  // This indicates the amount of memory that
  // is allocated at the start of each aggregate over a group.
  // This would typically be any memory allocated during the 
  // reset() call.
  //
  // external_bytes_per_row
  // This indicates the amount of memory that would be allocated
  // by the UDF for each row of a group.  This would typically
  // be memory allocated during next_value().
  //
  double            external_bytes_per_group;
  double            external_bytes_per_row;

  // Reserved fields for future use.  These must be initialized
  // to zero.
  a_sql_uint64      reserved6_must_be_null;
  a_sql_uint64      reserved7_must_be_null;
  a_sql_uint64      reserved8_must_be_null;
  a_sql_uint64      reserved9_must_be_null;
  a_sql_uint64      reserved10_must_be_null;

  //---------- For Server Internal Use Only -------------
  void  * _for_server_internal_use;

} a_extfn_aggregate;


// Indicator Bit Definitions

// For an unbounded OLAP query, is a single value returned for the entire set ?
// For example, a SUM() over an unbounded window would return the same value
// for each value in the set, while a RANK() function would return a different
// value for each row.  This indicator allows the engine to avoid duplicate,
// unnecessary calculations.
#define     EXTFNAPIV3_IND_SINGLEVALUERESULT    0x00000001 

// For unbounded OLAP queries, does the aggregate need to see future rows
// of the set before the value for a current position is calculated ?   This
// indicator allows the engine to use an algorithm uses the cumulative 
// evaluation API
#define     EXTFNAPIV3_IND_LOOKAHEADREQUIRED    0x00000002

// This indicator will disable the optimizer from assuming that multiple
// aggregate calculations can be made simulataneously.  This should be
// set for aggregate UDFs that have huge external resource requirements. 
#define     EXTFNAPIV3_IND_NOINTERLEAVEDCALC    0x00000004



#if defined( __cplusplus )
   }
#endif

#if defined( _SQL_PACK_STRUCTURES )
    #include "poppk.h"
    #if defined( _MSC_VER ) && _MSC_VER > 800
        #pragma warning(pop)
    #endif
#endif

#endif /* _EXTFNAPIV3_H_INCLUDED */
