; ModuleID = 'main'
source_filename = "main"

@_Const_String_ = private constant [5 x i8] c"%d\\n\00"

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)

define i32 @main() {
entry_point:
  %c = alloca i32
  %b = alloca i32
  %a = alloca i32
  store i32 3, i32* %a
  store i32 4, i32* %b
  store i32 0, i32* %c
  %tmpvar = load i32, i32* %a
  %tmp_rem_f = urem i32 %tmpvar, 2
  %tmpvar1 = load i32, i32* %b
  %tmp_mul_i = mul i32 %tmpvar1, 5
  %tmp_add_i = add i32 %tmp_rem_f, %tmp_mul_i
  store i32 %tmp_add_i, i32* %c
  %tmpvar2 = load i32, i32* %c
  %print_str = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @_Const_String_, i32 0, i32 0), i32 %tmpvar2)
  ret i32 0
}
