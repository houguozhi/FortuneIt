

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sat Jan 16 01:02:06 2016
 */
/* Compiler settings for FortuneIt.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __FortuneIt_h_h__
#define __FortuneIt_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IFortuneIt_FWD_DEFINED__
#define __IFortuneIt_FWD_DEFINED__
typedef interface IFortuneIt IFortuneIt;

#endif 	/* __IFortuneIt_FWD_DEFINED__ */


#ifndef __CFortuneItDoc_FWD_DEFINED__
#define __CFortuneItDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CFortuneItDoc CFortuneItDoc;
#else
typedef struct CFortuneItDoc CFortuneItDoc;
#endif /* __cplusplus */

#endif 	/* __CFortuneItDoc_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __FortuneIt_LIBRARY_DEFINED__
#define __FortuneIt_LIBRARY_DEFINED__

/* library FortuneIt */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_FortuneIt;

#ifndef __IFortuneIt_DISPINTERFACE_DEFINED__
#define __IFortuneIt_DISPINTERFACE_DEFINED__

/* dispinterface IFortuneIt */
/* [uuid] */ 


EXTERN_C const IID DIID_IFortuneIt;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B598BB9B-4D55-4515-B521-EFCDA96962B8")
    IFortuneIt : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IFortuneItVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFortuneIt * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFortuneIt * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFortuneIt * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IFortuneIt * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IFortuneIt * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IFortuneIt * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IFortuneIt * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IFortuneItVtbl;

    interface IFortuneIt
    {
        CONST_VTBL struct IFortuneItVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFortuneIt_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFortuneIt_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFortuneIt_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFortuneIt_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IFortuneIt_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IFortuneIt_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IFortuneIt_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IFortuneIt_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CFortuneItDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("E3E99A2A-3DDC-4D36-BFD0-F8C3DA6557EF")
CFortuneItDoc;
#endif
#endif /* __FortuneIt_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


