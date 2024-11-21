#ifndef LL_DEFAULT_IMPL_H
#define LL_DEFAULT_IMPL_H
#include "prelude.h"


/**
 * This virtual table keeping track of the resources held by the `LinkedList`.
 */
typedef struct {
  Destructor destructor;
  Clone clone;
  ComparisonFn compare;
} LinkedListVTable;


#ifdef _cplusplus
extern "C" {
#endif

/////////
// int //
/////////

int i32_compare(const i32* self,const i32* rhs);

void i32_clone(i32* dest,i32* src);

int u32_compare(const u32* self,const u32* rhs);

void u32_clone(u32* dest,u32* src);

int i64_compare(const i64* self,const i64* rhs);

void i64_clone(i64* dest,i64* src);

int u64_compare(const u64* self,const u64* rhs);

void u64_clone(u64* dest,u64* src);

int isize_compare(const isize* self,const isize* rhs);

void isize_clone(isize* dest,isize* src);

int usize_compare(const usize* self,const usize* rhs);

void usize_clone(usize* dest,usize* src);

int i128_compare(const i128* self,const i128* rhs);

void i128_clone(i128* dest,i128* src);

int u128_compare(const u128* self,const u128* rhs);

void u128_clone(u128* dest,u128* src);

int i16_compare(const i16* self,const i16* rhs);

void i16_clone(i16* dest,i16* src);

int u16_compare(const u16* self,const u16* rhs);

void u16_clone(u16* dest,u16* src);

int i8_compare(const i8* self,const i8* rhs);

void i8_clone(i8* dest,i8* src);

int u8_compare(const u8* self,const u8* rhs);

void u8_clone(u8* dest,u8* src);


///////////
// float //
///////////

int f32_compare(const f32* self,const f32* rhs);

void f32_clone(f32* dest,f32* src);

int f64_compare(const f64* self,const f64* rhs);

void f64_clone(f64* dest,f64* src);

int f16_compare(const f16* self,const f16* rhs);

void f16_clone(f16* dest,f16* src);

#ifdef __FLOAT128__
int f128_compare(const f128* self,const f128* rhs);

void f128_clone(f128* dest,f128* src);
#endif

//////////
// char //
//////////

int char_compare(const char* self,const char* rhs);

void char_clone(char* dest,char* src);

//////////
// bool //
//////////

int bool_compare(const bool* self,const bool* rhs);

void bool_clone(bool* dest,bool* src);


#ifdef _cplusplus
}
#endif


/////////
// int //
/////////

#define LL_VTABLE_I32 (LinkedListVTable) { \
  .destructor=NULL, \
  .compare=(ComparisonFn)i32_compare, \
  .clone=(Clone)i32_clone \
}

#define LL_VTABLE_U32 (LinkedListVTable) { \
  .destructor=NULL, \
  .compare=(ComparisonFn)u32_compare, \
  .clone=(Clone)u32_clone \
}

#define LL_VTABLE_I64 (LinkedListVTable) { \
  .destructor=NULL, \
  .compare=(ComparisonFn)i64_compare, \
  .clone=(Clone)i64_clone \
}

#define LL_VTABLE_U64 (LinkedListVTable) { \
  .destructor=NULL, \
  .compare=(ComparisonFn)u64_compare, \
  .clone=(Clone)u64_clone \
}

#define LL_VTABLE_ISIZE (LinkedListVTable) { \
  .destructor=NULL, \
  .compare=(ComparisonFn)isize_compare, \
  .clone=(Clone)isize_clone \
}

#define LL_VTABLE_USIZE (LinkedListVTable) { \
  .destructor=NULL, \
  .compare=(ComparisonFn)usize_compare, \
  .clone=(Clone)usize_clone \
}

#define LL_VTABLE_I128 (LinkedListVTable) { \
  .destructor=NULL, \
  .compare=(ComparisonFn)i128_compare, \
  .clone=(Clone)i128_clone \
}

#define LL_VTABLE_U128 (LinkedListVTable) { \
  .destructor=NULL, \
  .compare=(ComparisonFn)u128_compare, \
  .clone=(Clone)u128_clone \
}

#define LL_VTABLE_I16 (LinkedListVTable) { \
  .destructor=NULL, \
  .compare=(ComparisonFn)i16_compare, \
  .clone=(Clone)i16_clone \
}

#define LL_VTABLE_U16 (LinkedListVTable) { \
  .destructor=NULL, \
  .compare=(ComparisonFn)u16_compare, \
  .clone=(Clone)u16_clone \
}

#define LL_VTABLE_I8 (LinkedListVTable) { \
  .destructor=NULL, \
  .compare=(ComparisonFn)i8_compare, \
  .clone=(Clone)i8_clone \
}

#define LL_VTABLE_U8 (LinkedListVTable) { \
  .destructor=NULL, \
  .compare=(ComparisonFn)u8_compare, \
  .clone=(Clone)u8_clone \
}

///////////
// float //
///////////

#define LL_VTABLE_F32 (LinkedListVTable) { \
  .destructor=NULL, \
  .compare=(ComparisonFn)f32_compare, \
  .clone=(Clone)f32_clone \
}

#define LL_VTABLE_F64 (LinkedListVTable) { \
  .destructor=NULL, \
  .compare=(ComparisonFn)f64_compare, \
  .clone=(Clone)f64_clone \
}

#define LL_VTABLE_F16 (LinkedListVTable) { \
  .destructor=NULL, \
  .compare=(ComparisonFn)f16_compare, \
  .clone=(Clone)f16_clone \
}

#ifdef __FLOAT128__
#define LL_VTABLE_F128 (LinkedListVTable) { \
  .destructor=NULL, \
  .compare=(ComparisonFn)f128_compare, \
  .clone=(Clone)f128_clone \
}
#endif

//////////
// char //
//////////

#define LL_VTABLE_CHAR (LinkedListVTable) { \
  .destructor=NULL, \
  .compare=(ComparisonFn)char_compare, \
  .clone=(Clone)char_clone \
}

//////////
// bool //
//////////

#define LL_VTABLE_BOOL (LinkedListVTable) { \
  .destructor=NULL, \
  .compare=(ComparisonFn)bool_compare, \
  .clone=(Clone)bool_clone \
}




#endif
