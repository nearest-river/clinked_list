#include "default_impl.h"
#include "prelude.h"


/////////
// int //
/////////


inline_always
int i32_compare(const i32* self,const i32* rhs) {
  i32 a=*self;
  i32 b=*rhs;
  return a==b?0:a<b?-1:1;
}

inline_always
void i32_clone(i32* dest,i32* src) {
  *dest=*src;
}

inline_always
int u32_compare(const u32* self,const u32* rhs) {
  u32 a=*self;
  u32 b=*rhs;
  return a==b?0:a<b?-1:1;
}

inline_always
void u32_clone(u32* dest,u32* src) {
  *dest=*src;
}

inline_always
int i64_compare(const i64* self,const i64* rhs) {
  i64 a=*self;
  i64 b=*rhs;
  return a==b?0:a<b?-1:1;
}

inline_always
void i64_clone(i64* dest,i64* src) {
  *dest=*src;
}

inline_always
int u64_compare(const u64* self,const u64* rhs) {
  u64 a=*self;
  u64 b=*rhs;
  return a==b?0:a<b?-1:1;
}

inline_always
void u64_clone(u64* dest,u64* src) {
  *dest=*src;
}

inline_always
int isize_compare(const isize* self,const isize* rhs) {
  isize a=*self;
  isize b=*rhs;
  return a==b?0:a<b?-1:1;
}

inline_always
void isize_clone(isize* dest,isize* src) {
  *dest=*src;
}

inline_always
int usize_compare(const usize* self,const usize* rhs) {
  usize a=*self;
  usize b=*rhs;
  return a==b?0:a<b?-1:1;
}

inline_always
void usize_clone(usize* dest,usize* src) {
  *dest=*src;
}

inline_always
int i128_compare(const i128* self,const i128* rhs) {
  i128 a=*self;
  i128 b=*rhs;
  return a==b?0:a<b?-1:1;
}

inline_always
void i128_clone(i128* dest,i128* src) {
  *dest=*src;
}

inline_always
int u128_compare(const u128* self,const u128* rhs) {
  u128 a=*self;
  u128 b=*rhs;
  return a==b?0:a<b?-1:1;
}

inline_always
void u128_clone(u128* dest,u128* src) {
  *dest=*src;
}

inline_always
int i16_compare(const i16* self,const i16* rhs) {
  i16 a=*self;
  i16 b=*rhs;
  return a==b?0:a<b?-1:1;
}

inline_always
void i16_clone(i16* dest,i16* src) {
  *dest=*src;
}

inline_always
int u16_compare(const u16* self,const u16* rhs) {
  u16 a=*self;
  u16 b=*rhs;
  return a==b?0:a<b?-1:1;
}

inline_always
void u16_clone(u16* dest,u16* src) {
  *dest=*src;
}

inline_always
int i8_compare(const i8* self,const i8* rhs) {
  i8 a=*self;
  i8 b=*rhs;
  return a==b?0:a<b?-1:1;
}

inline_always
void i8_clone(i8* dest,i8* src) {
  *dest=*src;
}

inline_always
int u8_compare(const u8* self,const u8* rhs) {
  u8 a=*self;
  u8 b=*rhs;
  return a==b?0:a<b?-1:1;
}

inline_always
void u8_clone(u8* dest,u8* src) {
  *dest=*src;
}


///////////
// float //
///////////

inline_always
int f32_compare(const f32* self,const f32* rhs) {
  f32 a=*self;
  f32 b=*rhs;
  return a==b?0:a<b?-1:1;
}

inline_always
void f32_clone(f32* dest,f32* src) {
  *dest=*src;
}

inline_always
int f64_compare(const f64* self,const f64* rhs) {
  f64 a=*self;
  f64 b=*rhs;
  return a==b?0:a<b?-1:1;
}

inline_always
void f64_clone(f64* dest,f64* src) {
  *dest=*src;
}

inline_always
int f16_compare(const f16* self,const f16* rhs) {
  f16 a=*self;
  f16 b=*rhs;
  return a==b?0:a<b?-1:1;
}

inline_always
void f16_clone(f16* dest,f16* src) {
  *dest=*src;
}

#ifdef __FLOAT128__
inline_always
int f128_compare(const f128* self,const f128* rhs) {
  f128 a=*self;
  f128 b=*rhs;
  return a==b?0:a<b?-1:1;
}

inline_always
void f128_clone(f128* dest,f128* src) {
  *dest=*src;
}
#endif

//////////
// char //
//////////

inline_always
int char_compare(const char* self,const char* rhs) {
  char a=*self;
  char b=*rhs;
  return a==b?0:a<b?-1:1;
}

inline_always
void char_clone(char* dest,char* src) {
  *dest=*src;
}

//////////
// bool //
//////////

inline_always
int bool_compare(const bool* self,const bool* rhs) {
  bool a=*self;
  bool b=*rhs;
  return a==b?0:a<b?-1:1;
}

inline_always
void bool_clone(bool* dest,bool* src) {
  *dest=*src;
}


