
HEADERS+= \
csad/include/bt.h \

SOURCES+= \
csad/bt/baseclassarray.cpp \
csad/bt/functions.cpp \
csad/bt/memmanager.cpp \
csad/bt/string.cpp \
csad/bt/script.cpp \
csad/bt/parameterslist.cpp \
csad/bt/variant.cpp

SOURCES+= \
csad/bt/math/math.cpp

HEADERS+= \
csad/include/bt/os.h \
csad/include/bt/types.h \
csad/include/bt/basetypes.h \
csad/include/bt/typesproc.h \
csad/include/bt/functions.h \
csad/include/bt/macroscall.h \
csad/include/bt/macroscpu.h \
csad/include/bt/macrostype.h \
csad/include/bt/macrosos.h \
csad/include/bt/consts.h \
csad/include/bt/baseclassarray.h \
csad/include/bt/memmanager.h \
csad/include/bt/string.h \
csad/include/bt/script.h \
csad/include/bt/parameterslist.h \
csad/include/bt/array.h \
csad/include/bt/btapi.h \
csad/include/bt/variant.h \
csad/include/bt/math/math.h \
csad/include/bt/math/vector4b.h \
csad/include/bt/math/vector2i.h \
csad/include/bt/math/vector3i.h \
csad/include/bt/math/vector4i.h \
csad/include/bt/math/vector2f.h \
csad/include/bt/math/vector3f.h \
csad/include/bt/math/vector4f.h \
csad/include/bt/math/vector2d.h \
csad/include/bt/math/vector3d.h \
csad/include/bt/math/vector4d.h \
csad/include/bt/math/matrix4f.h \
csad/include/bt/math/matrix4d.h \
csad/include/bt/math/quaternionf.h \
csad/include/bt/math/quaterniond.h

SOURCES+= \
csad/bt/base/basevector.cpp \
csad/bt/base/baseext.cpp \
csad/bt/base/basemath.cpp \
csad/bt/base/basearrayvector.cpp \
csad/bt/base/basearray.cpp \
csad/bt/base/baserender.cpp

HEADERS+= \
csad/bt/base/baseapi.h \
csad/bt/base/basemath.h \
csad/bt/base/baseext.h \
csad/bt/base/basevector.h \
csad/bt/base/basearrayvector.h \
csad/bt/base/basearray.h \
csad/bt/base/baserender.h

SOURCES+= \
csad/bt/x86/x86cpu.cpp \
csad/bt/x86/x86container.cpp \
csad/bt/x86/x86functions.cpp \
csad/bt/x86/x86vector.cpp \
csad/bt/x86/x86quaternion.cpp \
csad/bt/x86/x86matrix.cpp \
csad/bt/x86/x86array.cpp \
csad/bt/x86/x86mem.cpp \
csad/bt/x86/x86extension.cpp \
csad/bt/x86/x86math.cpp \
csad/bt/x86/x86render.cpp

HEADERS+= \
csad/bt/x86/macrosasm.h \
csad/bt/x86/x86cpu.h \
csad/bt/x86/x86functions.h \
csad/bt/x86/x86container.h \
csad/bt/x86/x86vector.h \
csad/bt/x86/x86vector_to.h \
csad/bt/x86/x86vector_abs.h \
csad/bt/x86/x86vector_minmax.h \
csad/bt/x86/x86vector_add.h \
csad/bt/x86/x86vector_sub.h \
csad/bt/x86/x86vector_scale.h \
csad/bt/x86/x86vector_distance2.h \
csad/bt/x86/x86vector_mul.h \
csad/bt/x86/x86vector_div.h \
csad/bt/x86/x86vector_mul2n.h \
csad/bt/x86/x86vector_dotproduct.h \
csad/bt/x86/x86vector_cross.h \
csad/bt/x86/x86vector_length2.h \
csad/bt/x86/x86vector_lerp.h \
csad/bt/x86/x86vector_combine.h \
csad/bt/x86/x86vector_quaternion.h \
csad/bt/x86/x86vector_normal.h \
csad/bt/x86/x86vector_qdfl.h \
csad/bt/x86/x86vector_angle.h \
csad/bt/x86/x86vector_proj.h \
csad/bt/x86/x86vector_scale.h \
csad/bt/x86/x86vector_transform.h \
csad/bt/x86/x86vector_mmul.h \
csad/bt/x86/x86vector_bl.h \
csad/bt/x86/x86quaternion.h \
csad/bt/x86/x86quaternion_vector.h \
csad/bt/x86/x86quaternion_inv.h \
csad/bt/x86/x86quaternion_matrix.h \
csad/bt/x86/x86quaternion_transform.h \
csad/bt/x86/x86matrix.h \
csad/bt/x86/x86matrix_transpose.h \
csad/bt/x86/x86matrix_mul.h \
csad/bt/x86/x86matrix_trs.h \
csad/bt/x86/x86matrix_addtranslate.h \
csad/bt/x86/x86matrix_addscale.h \
csad/bt/x86/x86matrix_addrotate.h \
csad/bt/x86/x86array.h \
csad/bt/x86/x86array_add.h \
csad/bt/x86/x86array_sub.h \
csad/bt/x86/x86array_scale.h \
csad/bt/x86/x86array_mul.h \
csad/bt/x86/x86array_normal.h \
csad/bt/x86/x86array_transform.h \
csad/bt/x86/x86array_proj.h \
csad/bt/x86/x86mem.h \
csad/bt/x86/x86mem_clean.h \
csad/bt/x86/x86mem_move.h \
csad/bt/x86/x86mem_stos.h \
csad/bt/x86/x86extension.h \
csad/bt/x86/x86math.h \
csad/bt/x86/x86math_sincos.h \
csad/bt/x86/x86render.h \
csad/bt/x86/x86render_texel.h \
csad/bt/x86/x86render_span.h

SOURCES+= \
csad/bt/x86_64/x86_64cpu.cpp \
csad/bt/x86_64/x86_64functions.cpp \
csad/bt/x86_64/x86_64vector.cpp \
csad/bt/x86_64/x86_64matrix.cpp \
csad/bt/x86_64/x86_64quaternion.cpp \
csad/bt/x86_64/x86_64math.cpp \
csad/bt/x86_64/x86_64extension.cpp \
csad/bt/x86_64/x86_64mem.cpp

HEADERS+= \
csad/bt/x86_64/macrosasm.h \
csad/bt/x86_64/x86_64intrin.h \
csad/bt/x86_64/x86_64cpu.h \
csad/bt/x86_64/x86_64functions.h \
csad/bt/x86_64/x86_64sqrt.h \
csad/bt/x86_64/x86_64log2.h \
csad/bt/x86_64/x86_64vector.h \
csad/bt/x86_64/x86_64vector_add.h \
csad/bt/x86_64/x86_64vector_combine.h \
csad/bt/x86_64/x86_64vector_normal.h \
csad/bt/x86_64/x86_64vector_dotproduct.h \
csad/bt/x86_64/x86_64vector_lenght2.h \
csad/bt/x86_64/x86_64vector_lerp.h \
csad/bt/x86_64/x86_64matrix.h \
csad/bt/x86_64/x86_64quaternion.h \
csad/bt/x86_64/x86_64math.h \
csad/bt/x86_64/x86_64extension.h \
csad/bt/x86_64/x86_64mem.h

SOURCES+= \
csad/bt/e2k_64/e2k_64cpu.cpp \
csad/bt/e2k_64/e2k_64functions.cpp \
csad/bt/e2k_64/e2k_64vector.cpp \
csad/bt/e2k_64/e2k_64matrix.cpp \
csad/bt/e2k_64/e2k_64math.cpp

HEADERS+= \
csad/bt/e2k_64/e2k_64cpu.h \
csad/bt/e2k_64/e2k_64functions.h \
csad/bt/e2k_64/macrosasm.h \
csad/bt/e2k_64/e2k_64vector.h \
csad/bt/e2k_64/e2k_64matrix.h \
csad/bt/e2k_64/e2k_64math.h



