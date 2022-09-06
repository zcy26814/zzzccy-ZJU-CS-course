; ModuleID = 'main'
source_filename = "main"

@name = private global [5001 x i8] zeroinitializer
@lim = private global [1000001 x i8] zeroinitializer
@s = private global [101 x i32] zeroinitializer
@r = private global [101 x i32] zeroinitializer
@tmp = private global [1001 x i8] zeroinitializer
@x = private global i32 0
@tj = private global i32 0
@tk = private global i32 0
@0 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@_Const_String_ = private constant [8 x i8] c"GPA: %d\00"
@_Const_String_.1 = private constant [4 x i8] c".%d\00"
@_Const_String_.2 = private constant [1 x i8] zeroinitializer
@1 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@_Const_String_.3 = private constant [20 x i8] c"Hours Attempted: %d\00"
@_Const_String_.4 = private constant [1 x i8] zeroinitializer
@2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@_Const_String_.5 = private constant [20 x i8] c"Hours Completed: %d\00"
@_Const_String_.6 = private constant [1 x i8] zeroinitializer
@3 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@_Const_String_.7 = private constant [22 x i8] c"Credits Remaining: %d\00"
@_Const_String_.8 = private constant [1 x i8] zeroinitializer
@4 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@_Const_String_.9 = private constant [1 x i8] zeroinitializer
@5 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@_Const_String_.10 = private constant [31 x i8] c"Possible Courses to Take Next:\00"
@_Const_String_.11 = private constant [1 x i8] zeroinitializer
@6 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@_Const_String_.12 = private constant [26 x i8] c"  None - Congratulations!\00"
@7 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@_Const_String_.13 = private constant [3 x i8] c"  \00"
@_Const_String_.14 = private constant [3 x i8] c"%c\00"
@_Const_String_.15 = private constant [1 x i8] zeroinitializer
@8 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)

define i32 @check(i32 %j, i32 %k) {
entry_point:
  store i32 0, i32* @x
  store i32 %j, i32* @tj
  store i32 %k, i32* @tk
  br label %cond

cond:                                             ; preds = %merge, %entry_point
  %tmpvar = load i32, i32* @tk
  %tmpvar1 = load i32, i32* @tk
  %icmptmp = icmp sgt i32 %tmpvar1, 0
  %whileCond = icmp ne i1 %icmptmp, false
  br i1 %whileCond, label %loop, label %after_loop

loop:                                             ; preds = %cond
  %tmpvar2 = load i32, i32* @x
  %tmpvar3 = getelementptr inbounds [1001 x i8], [1001 x i8]* @tmp, i32 0, i32 %tmpvar2
  %tmpvar4 = load i8, i8* %tmpvar3
  %tmpvar5 = load i32, i32* @tj
  %tmpvar6 = getelementptr inbounds [5001 x i8], [5001 x i8]* @name, i32 0, i32 %tmpvar5
  %tmpvar7 = load i8, i8* %tmpvar6
  %tmpvar8 = load i32, i32* @x
  %tmpvar9 = getelementptr inbounds [1001 x i8], [1001 x i8]* @tmp, i32 0, i32 %tmpvar8
  %tmpvar10 = load i8, i8* %tmpvar9
  %tmpvar11 = load i32, i32* @tj
  %tmpvar12 = getelementptr inbounds [5001 x i8], [5001 x i8]* @name, i32 0, i32 %tmpvar11
  %tmpvar13 = load i8, i8* %tmpvar12
  %icmptmp14 = icmp ne i8 %tmpvar10, %tmpvar13
  %ifCond = icmp ne i1 %icmptmp14, false
  br i1 %ifCond, label %then, label %else

after_loop:                                       ; preds = %cond
  ret i32 1

then:                                             ; preds = %loop
  ret i32 0
  br label %merge

else:                                             ; preds = %loop
  br label %merge

merge:                                            ; preds = %else, %then
  %tmpvar15 = load i32, i32* @x
  %acop_add_i = add i32 %tmpvar15, 1
  store i32 %acop_add_i, i32* @x
  %tmpvar16 = load i32, i32* @tj
  %acop_add_i17 = add i32 %tmpvar16, 1
  store i32 %acop_add_i17, i32* @tj
  %tmpvar18 = load i32, i32* @tk
  %acop_sub_i = sub i32 %tmpvar18, 1
  store i32 %acop_sub_i, i32* @tk
  br label %cond
}

define i32 @main() {
entry_point:
  %cnt = alloca i32
  %lc = alloca i8
  %lb = alloca i8
  %la = alloca i8
  %ling = alloca i8
  %t = alloca i32
  %tok = alloca i32
  %ok = alloca i32
  %k = alloca i32
  %q = alloca i32
  %p = alloca i32
  %ch = alloca i8
  %j = alloca i32
  %i = alloca i32
  %end = alloca i32
  %n = alloca i32
  %ress = alloca i32
  %lrns = alloca i32
  %trys = alloca i32
  %gpa = alloca i32
  store i32 0, i32* %gpa
  store i32 0, i32* %trys
  store i32 0, i32* %lrns
  store i32 0, i32* %ress
  store i32 0, i32* %n
  store i32 0, i32* %end
  store i32 0, i32* %i
  store i32 0, i32* %j
  store i8 0, i8* %ch
  store i32 0, i32* %p
  store i32 0, i32* %q
  store i32 0, i32* %k
  store i32 0, i32* %ok
  store i32 0, i32* %tok
  store i32 0, i32* %t
  store i8 0, i8* %ling
  store i8 0, i8* %la
  store i8 0, i8* %lb
  store i8 0, i8* %lc
  br label %cond

cond:                                             ; preds = %merge, %entry_point
  %tmpvar = load i32, i32* %end
  %tmpvar1 = load i32, i32* %end
  %icmptmp = icmp ne i32 %tmpvar1, 1
  %whileCond = icmp ne i1 %icmptmp, false
  br i1 %whileCond, label %loop, label %after_loop

loop:                                             ; preds = %cond
  %tmpvar2 = load i8, i8* getelementptr inbounds ([1001 x i8], [1001 x i8]* @tmp, i32 0, i32 1)
  store i8 %tmpvar2, i8* %la
  %tmpvar3 = load i8, i8* getelementptr inbounds ([1001 x i8], [1001 x i8]* @tmp, i32 0, i32 2)
  store i8 %tmpvar3, i8* %lb
  %tmpvar4 = load i8, i8* getelementptr inbounds ([1001 x i8], [1001 x i8]* @tmp, i32 0, i32 3)
  store i8 %tmpvar4, i8* %lc
  %scanf = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @0, i32 0, i32 0), [1001 x i8]* @tmp)
  %tmpvar5 = load i8, i8* getelementptr inbounds ([1001 x i8], [1001 x i8]* @tmp, i32 0, i32 1)
  %tmpvar6 = load i8, i8* %la
  %tmpvar7 = load i8, i8* getelementptr inbounds ([1001 x i8], [1001 x i8]* @tmp, i32 0, i32 1)
  %tmpvar8 = load i8, i8* %la
  %icmptmp9 = icmp eq i8 %tmpvar7, %tmpvar8
  %tmpvar10 = load i8, i8* getelementptr inbounds ([1001 x i8], [1001 x i8]* @tmp, i32 0, i32 2)
  %tmpvar11 = load i8, i8* %lb
  %tmpvar12 = load i8, i8* getelementptr inbounds ([1001 x i8], [1001 x i8]* @tmp, i32 0, i32 2)
  %tmpvar13 = load i8, i8* %lb
  %icmptmp14 = icmp eq i8 %tmpvar12, %tmpvar13
  %tmp_and = and i1 %icmptmp9, %icmptmp14
  %tmpvar15 = load i8, i8* getelementptr inbounds ([1001 x i8], [1001 x i8]* @tmp, i32 0, i32 3)
  %tmpvar16 = load i8, i8* %lc
  %tmpvar17 = load i8, i8* getelementptr inbounds ([1001 x i8], [1001 x i8]* @tmp, i32 0, i32 3)
  %tmpvar18 = load i8, i8* %lc
  %icmptmp19 = icmp eq i8 %tmpvar17, %tmpvar18
  %tmp_and20 = and i1 %tmp_and, %icmptmp19
  %ifCond = icmp ne i1 %tmp_and20, false
  br i1 %ifCond, label %then, label %else

after_loop:                                       ; preds = %cond
  store i32 0, i32* %i
  br label %cond108

then:                                             ; preds = %loop
  store i32 1, i32* %end
  br label %merge

else:                                             ; preds = %loop
  store i32 0, i32* %i
  store i32 0, i32* %j
  br label %cond21

merge:                                            ; preds = %merge89, %then
  br label %cond

cond21:                                           ; preds = %loop22, %else
  %tmpvar24 = load i32, i32* %i
  %tmpvar25 = getelementptr inbounds [1001 x i8], [1001 x i8]* @tmp, i32 0, i32 %tmpvar24
  %tmpvar26 = load i8, i8* %tmpvar25
  %tmpvar27 = load i32, i32* %i
  %tmpvar28 = getelementptr inbounds [1001 x i8], [1001 x i8]* @tmp, i32 0, i32 %tmpvar27
  %tmpvar29 = load i8, i8* %tmpvar28
  %icmptmp30 = icmp ne i8 %tmpvar29, 124
  %whileCond31 = icmp ne i1 %icmptmp30, false
  br i1 %whileCond31, label %loop22, label %after_loop23

loop22:                                           ; preds = %cond21
  %tmpvar32 = load i32, i32* %n
  %tmp_mul_i = mul i32 %tmpvar32, 10
  %tmpvar33 = load i32, i32* %j
  %tmp_add_i = add i32 %tmp_mul_i, %tmpvar33
  %tmp_var = getelementptr inbounds [5001 x i8], [5001 x i8]* @name, i32 0, i32 %tmp_add_i
  %tmpvar34 = load i32, i32* %i
  %tmpvar35 = getelementptr inbounds [1001 x i8], [1001 x i8]* @tmp, i32 0, i32 %tmpvar34
  %tmpvar36 = load i8, i8* %tmpvar35
  store i8 %tmpvar36, i8* %tmp_var
  %tmpvar37 = load i32, i32* %i
  %acop_add_i = add i32 %tmpvar37, 1
  store i32 %acop_add_i, i32* %i
  %tmpvar38 = load i32, i32* %j
  %acop_add_i39 = add i32 %tmpvar38, 1
  store i32 %acop_add_i39, i32* %j
  br label %cond21

after_loop23:                                     ; preds = %cond21
  %tmpvar40 = load i32, i32* %i
  %acop_add_i41 = add i32 %tmpvar40, 1
  store i32 %acop_add_i41, i32* %i
  %tmpvar42 = load i32, i32* %n
  %tmp_var43 = getelementptr inbounds [101 x i32], [101 x i32]* @s, i32 0, i32 %tmpvar42
  %tmpvar44 = load i32, i32* %i
  %tmpvar45 = getelementptr inbounds [1001 x i8], [1001 x i8]* @tmp, i32 0, i32 %tmpvar44
  %tmpvar46 = load i8, i8* %tmpvar45
  %tmp_sub_i = sub i8 %tmpvar46, 48
  %tmp_type_cast = zext i8 %tmp_sub_i to i32
  store i32 %tmp_type_cast, i32* %tmp_var43
  %tmpvar47 = load i32, i32* %i
  %acop_add_i48 = add i32 %tmpvar47, 2
  store i32 %acop_add_i48, i32* %i
  store i32 0, i32* %j
  br label %cond49

cond49:                                           ; preds = %loop50, %after_loop23
  %tmpvar52 = load i32, i32* %i
  %tmpvar53 = getelementptr inbounds [1001 x i8], [1001 x i8]* @tmp, i32 0, i32 %tmpvar52
  %tmpvar54 = load i8, i8* %tmpvar53
  %tmpvar55 = load i32, i32* %i
  %tmpvar56 = getelementptr inbounds [1001 x i8], [1001 x i8]* @tmp, i32 0, i32 %tmpvar55
  %tmpvar57 = load i8, i8* %tmpvar56
  %icmptmp58 = icmp ne i8 %tmpvar57, 124
  %whileCond59 = icmp ne i1 %icmptmp58, false
  br i1 %whileCond59, label %loop50, label %after_loop51

loop50:                                           ; preds = %cond49
  %tmpvar60 = load i32, i32* %n
  %tmp_mul_i61 = mul i32 %tmpvar60, 500
  %tmpvar62 = load i32, i32* %j
  %tmp_add_i63 = add i32 %tmp_mul_i61, %tmpvar62
  %tmp_var64 = getelementptr inbounds [1000001 x i8], [1000001 x i8]* @lim, i32 0, i32 %tmp_add_i63
  %tmpvar65 = load i32, i32* %i
  %tmpvar66 = getelementptr inbounds [1001 x i8], [1001 x i8]* @tmp, i32 0, i32 %tmpvar65
  %tmpvar67 = load i8, i8* %tmpvar66
  store i8 %tmpvar67, i8* %tmp_var64
  %tmpvar68 = load i32, i32* %i
  %acop_add_i69 = add i32 %tmpvar68, 1
  store i32 %acop_add_i69, i32* %i
  %tmpvar70 = load i32, i32* %j
  %acop_add_i71 = add i32 %tmpvar70, 1
  store i32 %acop_add_i71, i32* %j
  br label %cond49

after_loop51:                                     ; preds = %cond49
  %tmpvar72 = load i32, i32* %n
  %tmp_mul_i73 = mul i32 %tmpvar72, 500
  %tmpvar74 = load i32, i32* %j
  %tmp_add_i75 = add i32 %tmp_mul_i73, %tmpvar74
  %tmp_var76 = getelementptr inbounds [1000001 x i8], [1000001 x i8]* @lim, i32 0, i32 %tmp_add_i75
  store i8 59, i8* %tmp_var76
  %tmpvar77 = load i32, i32* %i
  %acop_add_i78 = add i32 %tmpvar77, 1
  store i32 %acop_add_i78, i32* %i
  %tmpvar79 = load i32, i32* %i
  %tmpvar80 = getelementptr inbounds [1001 x i8], [1001 x i8]* @tmp, i32 0, i32 %tmpvar79
  %tmpvar81 = load i8, i8* %tmpvar80
  store i8 %tmpvar81, i8* %ch
  %tmpvar82 = load i8, i8* %ch
  %tmpvar83 = load i8, i8* %ch
  %tmp_type_cast84 = zext i8 %tmpvar83 to i32
  %icmptmp85 = icmp eq i32 %tmp_type_cast84, 0
  %ifCond86 = icmp ne i1 %icmptmp85, false
  br i1 %ifCond86, label %then87, label %else88

then87:                                           ; preds = %after_loop51
  %tmpvar90 = load i32, i32* %n
  %tmp_var91 = getelementptr inbounds [101 x i32], [101 x i32]* @r, i32 0, i32 %tmpvar90
  store i32 -1, i32* %tmp_var91
  br label %merge89

else88:                                           ; preds = %after_loop51
  %tmpvar92 = load i8, i8* %ch
  %tmpvar93 = load i8, i8* %ch
  %icmptmp94 = icmp eq i8 %tmpvar93, 70
  %ifCond95 = icmp ne i1 %icmptmp94, false
  br i1 %ifCond95, label %then96, label %else97

merge89:                                          ; preds = %merge98, %then87
  %tmpvar106 = load i32, i32* %n
  %acop_add_i107 = add i32 %tmpvar106, 1
  store i32 %acop_add_i107, i32* %n
  br label %merge

then96:                                           ; preds = %else88
  %tmpvar99 = load i32, i32* %n
  %tmp_var100 = getelementptr inbounds [101 x i32], [101 x i32]* @r, i32 0, i32 %tmpvar99
  store i32 0, i32* %tmp_var100
  br label %merge98

else97:                                           ; preds = %else88
  %tmpvar101 = load i32, i32* %n
  %tmp_var102 = getelementptr inbounds [101 x i32], [101 x i32]* @r, i32 0, i32 %tmpvar101
  %tmpvar103 = load i8, i8* %ch
  %tmp_sub_i104 = sub i8 69, %tmpvar103
  %tmp_type_cast105 = zext i8 %tmp_sub_i104 to i32
  store i32 %tmp_type_cast105, i32* %tmp_var102
  br label %merge98

merge98:                                          ; preds = %else97, %then96
  br label %merge89

cond108:                                          ; preds = %merge164, %after_loop
  %tmpvar111 = load i32, i32* %i
  %tmpvar112 = load i32, i32* %n
  %tmpvar113 = load i32, i32* %i
  %tmpvar114 = load i32, i32* %n
  %icmptmp115 = icmp slt i32 %tmpvar113, %tmpvar114
  %whileCond116 = icmp ne i1 %icmptmp115, false
  br i1 %whileCond116, label %loop109, label %after_loop110

loop109:                                          ; preds = %cond108
  %tmpvar117 = load i32, i32* %i
  %tmpvar118 = getelementptr inbounds [101 x i32], [101 x i32]* @r, i32 0, i32 %tmpvar117
  %tmpvar119 = load i32, i32* %tmpvar118
  %tmpvar120 = load i32, i32* %i
  %tmpvar121 = getelementptr inbounds [101 x i32], [101 x i32]* @r, i32 0, i32 %tmpvar120
  %tmpvar122 = load i32, i32* %tmpvar121
  %icmptmp123 = icmp eq i32 %tmpvar122, 0
  %ifCond124 = icmp ne i1 %icmptmp123, false
  br i1 %ifCond124, label %then125, label %else126

after_loop110:                                    ; preds = %cond108
  %tmpvar186 = load i32, i32* %gpa
  %acop_mul_i = mul i32 %tmpvar186, 10
  store i32 %acop_mul_i, i32* %gpa
  %tmpvar187 = load i32, i32* %trys
  %tmpvar188 = load i32, i32* %trys
  %icmptmp189 = icmp ne i32 %tmpvar188, 0
  %ifCond190 = icmp ne i1 %icmptmp189, false
  br i1 %ifCond190, label %then191, label %else192

then125:                                          ; preds = %loop109
  %tmpvar128 = load i32, i32* %i
  %tmpvar129 = getelementptr inbounds [101 x i32], [101 x i32]* @s, i32 0, i32 %tmpvar128
  %tmpvar130 = load i32, i32* %tmpvar129
  %tmpvar131 = load i32, i32* %trys
  %acop_add_i132 = add i32 %tmpvar131, %tmpvar130
  store i32 %acop_add_i132, i32* %trys
  %tmpvar133 = load i32, i32* %i
  %tmpvar134 = getelementptr inbounds [101 x i32], [101 x i32]* @s, i32 0, i32 %tmpvar133
  %tmpvar135 = load i32, i32* %tmpvar134
  %tmpvar136 = load i32, i32* %ress
  %acop_add_i137 = add i32 %tmpvar136, %tmpvar135
  store i32 %acop_add_i137, i32* %ress
  br label %merge127

else126:                                          ; preds = %loop109
  br label %merge127

merge127:                                         ; preds = %else126, %then125
  %tmpvar138 = load i32, i32* %i
  %tmpvar139 = getelementptr inbounds [101 x i32], [101 x i32]* @r, i32 0, i32 %tmpvar138
  %tmpvar140 = load i32, i32* %tmpvar139
  %tmpvar141 = load i32, i32* %i
  %tmpvar142 = getelementptr inbounds [101 x i32], [101 x i32]* @r, i32 0, i32 %tmpvar141
  %tmpvar143 = load i32, i32* %tmpvar142
  %icmptmp144 = icmp eq i32 %tmpvar143, -1
  %ifCond145 = icmp ne i1 %icmptmp144, false
  br i1 %ifCond145, label %then146, label %else147

then146:                                          ; preds = %merge127
  %tmpvar149 = load i32, i32* %i
  %tmpvar150 = getelementptr inbounds [101 x i32], [101 x i32]* @s, i32 0, i32 %tmpvar149
  %tmpvar151 = load i32, i32* %tmpvar150
  %tmpvar152 = load i32, i32* %ress
  %acop_add_i153 = add i32 %tmpvar152, %tmpvar151
  store i32 %acop_add_i153, i32* %ress
  br label %merge148

else147:                                          ; preds = %merge127
  br label %merge148

merge148:                                         ; preds = %else147, %then146
  %tmpvar154 = load i32, i32* %i
  %tmpvar155 = getelementptr inbounds [101 x i32], [101 x i32]* @r, i32 0, i32 %tmpvar154
  %tmpvar156 = load i32, i32* %tmpvar155
  %tmpvar157 = load i32, i32* %i
  %tmpvar158 = getelementptr inbounds [101 x i32], [101 x i32]* @r, i32 0, i32 %tmpvar157
  %tmpvar159 = load i32, i32* %tmpvar158
  %icmptmp160 = icmp sgt i32 %tmpvar159, 0
  %ifCond161 = icmp ne i1 %icmptmp160, false
  br i1 %ifCond161, label %then162, label %else163

then162:                                          ; preds = %merge148
  %tmpvar165 = load i32, i32* %i
  %tmpvar166 = getelementptr inbounds [101 x i32], [101 x i32]* @s, i32 0, i32 %tmpvar165
  %tmpvar167 = load i32, i32* %tmpvar166
  %tmpvar168 = load i32, i32* %trys
  %acop_add_i169 = add i32 %tmpvar168, %tmpvar167
  store i32 %acop_add_i169, i32* %trys
  %tmpvar170 = load i32, i32* %i
  %tmpvar171 = getelementptr inbounds [101 x i32], [101 x i32]* @s, i32 0, i32 %tmpvar170
  %tmpvar172 = load i32, i32* %tmpvar171
  %tmpvar173 = load i32, i32* %lrns
  %acop_add_i174 = add i32 %tmpvar173, %tmpvar172
  store i32 %acop_add_i174, i32* %lrns
  %tmpvar175 = load i32, i32* %i
  %tmpvar176 = getelementptr inbounds [101 x i32], [101 x i32]* @r, i32 0, i32 %tmpvar175
  %tmpvar177 = load i32, i32* %tmpvar176
  %tmpvar178 = load i32, i32* %i
  %tmpvar179 = getelementptr inbounds [101 x i32], [101 x i32]* @s, i32 0, i32 %tmpvar178
  %tmpvar180 = load i32, i32* %tmpvar179
  %tmp_mul_i181 = mul i32 %tmpvar177, %tmpvar180
  %tmpvar182 = load i32, i32* %gpa
  %acop_add_i183 = add i32 %tmpvar182, %tmp_mul_i181
  store i32 %acop_add_i183, i32* %gpa
  br label %merge164

else163:                                          ; preds = %merge148
  br label %merge164

merge164:                                         ; preds = %else163, %then162
  %tmpvar184 = load i32, i32* %i
  %acop_add_i185 = add i32 %tmpvar184, 1
  store i32 %acop_add_i185, i32* %i
  br label %cond108

then191:                                          ; preds = %after_loop110
  %tmpvar194 = load i32, i32* %trys
  %tmpvar195 = load i32, i32* %gpa
  %acop_mul_f = sdiv i32 %tmpvar195, %tmpvar194
  store i32 %acop_mul_f, i32* %gpa
  br label %merge193

else192:                                          ; preds = %after_loop110
  store i32 0, i32* %gpa
  br label %merge193

merge193:                                         ; preds = %else192, %then191
  %tmpvar196 = load i32, i32* %gpa
  %tmp_mul_f = sdiv i32 %tmpvar196, 10
  %print_str = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @_Const_String_, i32 0, i32 0), i32 %tmp_mul_f)
  %tmpvar197 = load i32, i32* %gpa
  %tmp_rem_f = urem i32 %tmpvar197, 10
  %print_str198 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @_Const_String_.1, i32 0, i32 0), i32 %tmp_rem_f)
  %print_str199 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([1 x i8], [1 x i8]* @_Const_String_.2, i32 0, i32 0))
  %println_token = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @1, i32 0, i32 0))
  %tmpvar200 = load i32, i32* %trys
  %print_str201 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @_Const_String_.3, i32 0, i32 0), i32 %tmpvar200)
  %print_str202 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([1 x i8], [1 x i8]* @_Const_String_.4, i32 0, i32 0))
  %println_token203 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @2, i32 0, i32 0))
  %tmpvar204 = load i32, i32* %lrns
  %print_str205 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @_Const_String_.5, i32 0, i32 0), i32 %tmpvar204)
  %print_str206 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([1 x i8], [1 x i8]* @_Const_String_.6, i32 0, i32 0))
  %println_token207 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @3, i32 0, i32 0))
  %tmpvar208 = load i32, i32* %ress
  %print_str209 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @_Const_String_.7, i32 0, i32 0), i32 %tmpvar208)
  %print_str210 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([1 x i8], [1 x i8]* @_Const_String_.8, i32 0, i32 0))
  %println_token211 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @4, i32 0, i32 0))
  %print_str212 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([1 x i8], [1 x i8]* @_Const_String_.9, i32 0, i32 0))
  %println_token213 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @5, i32 0, i32 0))
  %print_str214 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @_Const_String_.10, i32 0, i32 0))
  %print_str215 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([1 x i8], [1 x i8]* @_Const_String_.11, i32 0, i32 0))
  %println_token216 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @6, i32 0, i32 0))
  %tmpvar217 = load i32, i32* %ress
  %tmpvar218 = load i32, i32* %ress
  %icmptmp219 = icmp eq i32 %tmpvar218, 0
  %ifCond220 = icmp ne i1 %icmptmp219, false
  br i1 %ifCond220, label %then221, label %else222

then221:                                          ; preds = %merge193
  %print_str224 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @_Const_String_.12, i32 0, i32 0))
  %println_token225 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @7, i32 0, i32 0))
  ret i32 0
  br label %merge223

else222:                                          ; preds = %merge193
  br label %merge223

merge223:                                         ; preds = %else222, %then221
  store i32 0, i32* %i
  br label %cond226

cond226:                                          ; preds = %merge414, %merge223
  %tmpvar229 = load i32, i32* %i
  %tmpvar230 = load i32, i32* %n
  %tmpvar231 = load i32, i32* %i
  %tmpvar232 = load i32, i32* %n
  %icmptmp233 = icmp slt i32 %tmpvar231, %tmpvar232
  %whileCond234 = icmp ne i1 %icmptmp233, false
  br i1 %whileCond234, label %loop227, label %after_loop228

loop227:                                          ; preds = %cond226
  store i32 0, i32* %j
  store i32 0, i32* %ok
  store i32 1, i32* %tok
  store i32 0, i32* %k
  br label %cond235

after_loop228:                                    ; preds = %cond226
  ret i32 0

cond235:                                          ; preds = %merge266, %loop227
  %tmpvar238 = load i32, i32* %i
  %tmp_mul_i239 = mul i32 %tmpvar238, 500
  %tmpvar240 = load i32, i32* %j
  %tmp_add_i241 = add i32 %tmp_mul_i239, %tmpvar240
  %tmpvar242 = getelementptr inbounds [1000001 x i8], [1000001 x i8]* @lim, i32 0, i32 %tmp_add_i241
  %tmpvar243 = load i8, i8* %tmpvar242
  %tmpvar244 = load i8, i8* %ling
  %tmpvar245 = load i32, i32* %i
  %tmp_mul_i246 = mul i32 %tmpvar245, 500
  %tmpvar247 = load i32, i32* %j
  %tmp_add_i248 = add i32 %tmp_mul_i246, %tmpvar247
  %tmpvar249 = getelementptr inbounds [1000001 x i8], [1000001 x i8]* @lim, i32 0, i32 %tmp_add_i248
  %tmpvar250 = load i8, i8* %tmpvar249
  %tmpvar251 = load i8, i8* %ling
  %icmptmp252 = icmp ne i8 %tmpvar250, %tmpvar251
  %whileCond253 = icmp ne i1 %icmptmp252, false
  br i1 %whileCond253, label %loop236, label %after_loop237

loop236:                                          ; preds = %cond235
  %tmpvar254 = load i32, i32* %i
  %tmp_mul_i255 = mul i32 %tmpvar254, 500
  %tmpvar256 = load i32, i32* %j
  %tmp_add_i257 = add i32 %tmp_mul_i255, %tmpvar256
  %tmpvar258 = getelementptr inbounds [1000001 x i8], [1000001 x i8]* @lim, i32 0, i32 %tmp_add_i257
  %tmpvar259 = load i8, i8* %tmpvar258
  store i8 %tmpvar259, i8* %ch
  %tmpvar260 = load i8, i8* %ch
  %tmpvar261 = load i8, i8* %ch
  %icmptmp262 = icmp eq i8 %tmpvar261, 59
  %ifCond263 = icmp ne i1 %icmptmp262, false
  br i1 %ifCond263, label %then264, label %else265

after_loop237:                                    ; preds = %cond235
  %tmpvar400 = load i32, i32* %ok
  %tmpvar401 = load i32, i32* %ok
  %icmptmp402 = icmp eq i32 %tmpvar401, 1
  %tmpvar403 = load i32, i32* %i
  %tmpvar404 = getelementptr inbounds [101 x i32], [101 x i32]* @r, i32 0, i32 %tmpvar403
  %tmpvar405 = load i32, i32* %tmpvar404
  %tmpvar406 = load i32, i32* %i
  %tmpvar407 = getelementptr inbounds [101 x i32], [101 x i32]* @r, i32 0, i32 %tmpvar406
  %tmpvar408 = load i32, i32* %tmpvar407
  %icmptmp409 = icmp sle i32 %tmpvar408, 0
  %tmp_and410 = and i1 %icmptmp402, %icmptmp409
  %ifCond411 = icmp ne i1 %tmp_and410, false
  br i1 %ifCond411, label %then412, label %else413

then264:                                          ; preds = %loop236
  %tmpvar267 = load i32, i32* %k
  %tmpvar268 = load i32, i32* %k
  %icmptmp269 = icmp ne i32 %tmpvar268, 0
  %ifCond270 = icmp ne i1 %icmptmp269, false
  br i1 %ifCond270, label %then271, label %else272

else265:                                          ; preds = %loop236
  %tmpvar333 = load i8, i8* %ch
  %tmpvar334 = load i8, i8* %ch
  %icmptmp335 = icmp eq i8 %tmpvar334, 44
  %ifCond336 = icmp ne i1 %icmptmp335, false
  br i1 %ifCond336, label %then337, label %else338

merge266:                                         ; preds = %merge339, %merge332
  %tmpvar398 = load i32, i32* %j
  %acop_add_i399 = add i32 %tmpvar398, 1
  store i32 %acop_add_i399, i32* %j
  br label %cond235

then271:                                          ; preds = %then264
  %tmpvar274 = load i32, i32* %k
  %tmp_var275 = getelementptr inbounds [1001 x i8], [1001 x i8]* @tmp, i32 0, i32 %tmpvar274
  store i8 0, i8* %tmp_var275
  %tmpvar276 = load i32, i32* %k
  %tmp_add_i277 = add i32 %tmpvar276, 1
  %tmp_var278 = getelementptr inbounds [1001 x i8], [1001 x i8]* @tmp, i32 0, i32 %tmp_add_i277
  store i8 0, i8* %tmp_var278
  %tmpvar279 = load i32, i32* %k
  %tmp_add_i280 = add i32 %tmpvar279, 2
  %tmp_var281 = getelementptr inbounds [1001 x i8], [1001 x i8]* @tmp, i32 0, i32 %tmp_add_i280
  store i8 0, i8* %tmp_var281
  store i32 0, i32* %p
  store i32 -1, i32* %q
  br label %cond282

else272:                                          ; preds = %then264
  br label %merge273

merge273:                                         ; preds = %else272, %merge314
  %tmpvar326 = load i32, i32* %tok
  %tmpvar327 = load i32, i32* %tok
  %icmptmp328 = icmp eq i32 %tmpvar327, 1
  %ifCond329 = icmp ne i1 %icmptmp328, false
  br i1 %ifCond329, label %then330, label %else331

cond282:                                          ; preds = %merge304, %then271
  %tmpvar285 = load i32, i32* %p
  %tmpvar286 = load i32, i32* %n
  %tmpvar287 = load i32, i32* %p
  %tmpvar288 = load i32, i32* %n
  %icmptmp289 = icmp slt i32 %tmpvar287, %tmpvar288
  %whileCond290 = icmp ne i1 %icmptmp289, false
  br i1 %whileCond290, label %loop283, label %after_loop284

loop283:                                          ; preds = %cond282
  store i32 0, i32* %cnt
  %tmpvar291 = load i32, i32* %p
  %tmp_mul_i292 = mul i32 %tmpvar291, 10
  %tmpvar293 = load i32, i32* %k
  %tmp_add_i294 = add i32 %tmpvar293, 2
  %call_tmp = call i32 @check(i32 %tmp_mul_i292, i32 %tmp_add_i294)
  %tmpvar295 = load i32, i32* %p
  %tmp_mul_i296 = mul i32 %tmpvar295, 10
  %tmpvar297 = load i32, i32* %k
  %tmp_add_i298 = add i32 %tmpvar297, 2
  %call_tmp299 = call i32 @check(i32 %tmp_mul_i296, i32 %tmp_add_i298)
  %icmptmp300 = icmp eq i32 %call_tmp299, 1
  %ifCond301 = icmp ne i1 %icmptmp300, false
  br i1 %ifCond301, label %then302, label %else303

after_loop284:                                    ; preds = %cond282
  %tmpvar308 = load i32, i32* %q
  %tmpvar309 = load i32, i32* %q
  %icmptmp310 = icmp eq i32 %tmpvar309, -1
  %ifCond311 = icmp ne i1 %icmptmp310, false
  br i1 %ifCond311, label %then312, label %else313

then302:                                          ; preds = %loop283
  %tmpvar305 = load i32, i32* %p
  store i32 %tmpvar305, i32* %q
  br label %merge304

else303:                                          ; preds = %loop283
  br label %merge304

merge304:                                         ; preds = %else303, %then302
  %tmpvar306 = load i32, i32* %p
  %acop_add_i307 = add i32 %tmpvar306, 1
  store i32 %acop_add_i307, i32* %p
  br label %cond282

then312:                                          ; preds = %after_loop284
  store i32 0, i32* %tok
  br label %merge314

else313:                                          ; preds = %after_loop284
  %tmpvar315 = load i32, i32* %q
  %tmpvar316 = getelementptr inbounds [101 x i32], [101 x i32]* @r, i32 0, i32 %tmpvar315
  %tmpvar317 = load i32, i32* %tmpvar316
  %tmpvar318 = load i32, i32* %q
  %tmpvar319 = getelementptr inbounds [101 x i32], [101 x i32]* @r, i32 0, i32 %tmpvar318
  %tmpvar320 = load i32, i32* %tmpvar319
  %icmptmp321 = icmp sle i32 %tmpvar320, 0
  %ifCond322 = icmp ne i1 %icmptmp321, false
  br i1 %ifCond322, label %then323, label %else324

merge314:                                         ; preds = %merge325, %then312
  store i32 0, i32* %k
  br label %merge273

then323:                                          ; preds = %else313
  store i32 0, i32* %tok
  br label %merge325

else324:                                          ; preds = %else313
  br label %merge325

merge325:                                         ; preds = %else324, %then323
  br label %merge314

then330:                                          ; preds = %merge273
  store i32 1, i32* %ok
  br label %merge332

else331:                                          ; preds = %merge273
  br label %merge332

merge332:                                         ; preds = %else331, %then330
  store i32 1, i32* %tok
  store i32 0, i32* %k
  br label %merge266

then337:                                          ; preds = %else265
  %tmpvar340 = load i32, i32* %k
  %tmp_var341 = getelementptr inbounds [1001 x i8], [1001 x i8]* @tmp, i32 0, i32 %tmpvar340
  store i8 0, i8* %tmp_var341
  %tmpvar342 = load i32, i32* %k
  %tmp_add_i343 = add i32 %tmpvar342, 1
  %tmp_var344 = getelementptr inbounds [1001 x i8], [1001 x i8]* @tmp, i32 0, i32 %tmp_add_i343
  store i8 0, i8* %tmp_var344
  %tmpvar345 = load i32, i32* %k
  %tmp_add_i346 = add i32 %tmpvar345, 2
  %tmp_var347 = getelementptr inbounds [1001 x i8], [1001 x i8]* @tmp, i32 0, i32 %tmp_add_i346
  store i8 0, i8* %tmp_var347
  store i32 0, i32* %p
  store i32 -1, i32* %q
  br label %cond348

else338:                                          ; preds = %else265
  %tmpvar393 = load i32, i32* %k
  %tmp_var394 = getelementptr inbounds [1001 x i8], [1001 x i8]* @tmp, i32 0, i32 %tmpvar393
  %tmpvar395 = load i8, i8* %ch
  store i8 %tmpvar395, i8* %tmp_var394
  %tmpvar396 = load i32, i32* %k
  %acop_add_i397 = add i32 %tmpvar396, 1
  store i32 %acop_add_i397, i32* %k
  br label %merge339

merge339:                                         ; preds = %else338, %merge381
  br label %merge266

cond348:                                          ; preds = %merge371, %then337
  %tmpvar351 = load i32, i32* %p
  %tmpvar352 = load i32, i32* %n
  %tmpvar353 = load i32, i32* %p
  %tmpvar354 = load i32, i32* %n
  %icmptmp355 = icmp slt i32 %tmpvar353, %tmpvar354
  %whileCond356 = icmp ne i1 %icmptmp355, false
  br i1 %whileCond356, label %loop349, label %after_loop350

loop349:                                          ; preds = %cond348
  %tmpvar357 = load i32, i32* %p
  %tmp_mul_i358 = mul i32 %tmpvar357, 10
  %tmpvar359 = load i32, i32* %k
  %tmp_add_i360 = add i32 %tmpvar359, 2
  %call_tmp361 = call i32 @check(i32 %tmp_mul_i358, i32 %tmp_add_i360)
  %tmpvar362 = load i32, i32* %p
  %tmp_mul_i363 = mul i32 %tmpvar362, 10
  %tmpvar364 = load i32, i32* %k
  %tmp_add_i365 = add i32 %tmpvar364, 2
  %call_tmp366 = call i32 @check(i32 %tmp_mul_i363, i32 %tmp_add_i365)
  %icmptmp367 = icmp eq i32 %call_tmp366, 1
  %ifCond368 = icmp ne i1 %icmptmp367, false
  br i1 %ifCond368, label %then369, label %else370

after_loop350:                                    ; preds = %cond348
  %tmpvar375 = load i32, i32* %q
  %tmpvar376 = load i32, i32* %q
  %icmptmp377 = icmp eq i32 %tmpvar376, -1
  %ifCond378 = icmp ne i1 %icmptmp377, false
  br i1 %ifCond378, label %then379, label %else380

then369:                                          ; preds = %loop349
  %tmpvar372 = load i32, i32* %p
  store i32 %tmpvar372, i32* %q
  br label %merge371

else370:                                          ; preds = %loop349
  br label %merge371

merge371:                                         ; preds = %else370, %then369
  %tmpvar373 = load i32, i32* %p
  %acop_add_i374 = add i32 %tmpvar373, 1
  store i32 %acop_add_i374, i32* %p
  br label %cond348

then379:                                          ; preds = %after_loop350
  store i32 0, i32* %tok
  br label %merge381

else380:                                          ; preds = %after_loop350
  %tmpvar382 = load i32, i32* %q
  %tmpvar383 = getelementptr inbounds [101 x i32], [101 x i32]* @r, i32 0, i32 %tmpvar382
  %tmpvar384 = load i32, i32* %tmpvar383
  %tmpvar385 = load i32, i32* %q
  %tmpvar386 = getelementptr inbounds [101 x i32], [101 x i32]* @r, i32 0, i32 %tmpvar385
  %tmpvar387 = load i32, i32* %tmpvar386
  %icmptmp388 = icmp sle i32 %tmpvar387, 0
  %ifCond389 = icmp ne i1 %icmptmp388, false
  br i1 %ifCond389, label %then390, label %else391

merge381:                                         ; preds = %merge392, %then379
  store i32 0, i32* %k
  br label %merge339

then390:                                          ; preds = %else380
  store i32 0, i32* %tok
  br label %merge392

else391:                                          ; preds = %else380
  br label %merge392

merge392:                                         ; preds = %else391, %then390
  br label %merge381

then412:                                          ; preds = %after_loop237
  %print_str415 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_Const_String_.13, i32 0, i32 0))
  store i32 0, i32* %t
  br label %cond416

else413:                                          ; preds = %after_loop237
  br label %merge414

merge414:                                         ; preds = %else413, %after_loop418
  %tmpvar446 = load i32, i32* %i
  %acop_add_i447 = add i32 %tmpvar446, 1
  store i32 %acop_add_i447, i32* %i
  br label %cond226

cond416:                                          ; preds = %loop417, %then412
  %tmpvar419 = load i32, i32* %i
  %tmp_mul_i420 = mul i32 %tmpvar419, 10
  %tmpvar421 = load i32, i32* %t
  %tmp_add_i422 = add i32 %tmp_mul_i420, %tmpvar421
  %tmpvar423 = getelementptr inbounds [5001 x i8], [5001 x i8]* @name, i32 0, i32 %tmp_add_i422
  %tmpvar424 = load i8, i8* %tmpvar423
  %tmpvar425 = load i8, i8* %ling
  %tmpvar426 = load i32, i32* %i
  %tmp_mul_i427 = mul i32 %tmpvar426, 10
  %tmpvar428 = load i32, i32* %t
  %tmp_add_i429 = add i32 %tmp_mul_i427, %tmpvar428
  %tmpvar430 = getelementptr inbounds [5001 x i8], [5001 x i8]* @name, i32 0, i32 %tmp_add_i429
  %tmpvar431 = load i8, i8* %tmpvar430
  %tmpvar432 = load i8, i8* %ling
  %icmptmp433 = icmp ne i8 %tmpvar431, %tmpvar432
  %whileCond434 = icmp ne i1 %icmptmp433, false
  br i1 %whileCond434, label %loop417, label %after_loop418

loop417:                                          ; preds = %cond416
  %tmpvar435 = load i32, i32* %i
  %tmp_mul_i436 = mul i32 %tmpvar435, 10
  %tmpvar437 = load i32, i32* %t
  %tmp_add_i438 = add i32 %tmp_mul_i436, %tmpvar437
  %tmpvar439 = getelementptr inbounds [5001 x i8], [5001 x i8]* @name, i32 0, i32 %tmp_add_i438
  %tmpvar440 = load i8, i8* %tmpvar439
  %print_str441 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_Const_String_.14, i32 0, i32 0), i8 %tmpvar440)
  %tmpvar442 = load i32, i32* %t
  %acop_add_i443 = add i32 %tmpvar442, 1
  store i32 %acop_add_i443, i32* %t
  br label %cond416

after_loop418:                                    ; preds = %cond416
  %print_str444 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([1 x i8], [1 x i8]* @_Const_String_.15, i32 0, i32 0))
  %println_token445 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @8, i32 0, i32 0))
  br label %merge414
}
