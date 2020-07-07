/*
 * Define templates for given (predefined) type __TYPE.
 *
 * __TYPE_IS_UNSIGNED must be defined as 1 if __TYPE is unsigned, 0 otherwise.
 *     For signed types __UNSIGNED_OF_##__TYPE must be defined as corresponding
 *     unsigned type with at least the same size.
 *
 * __TYPE_HAS_EXTENSION must be defined as 1 if there is a type of the same sign
 * with at least doubled size of __TYPE (extended type), 0 otherwise.
 *     For types with extension __EXTENDED_OF_##__TYPE must be defined as
 *     corresponding extended type.
 *     if __TYPE is signed and has an extension, an extended version of
 *     __UNSIGNED_OF_##__TYPE must be defined.
 *
 *
 * Определить шаблоны для заданного (предопределённого) типа __TYPE.
 *
 * __TYPE_IS_UNSIGNED должно быть определено как 1, если __TYPE беззнаковый,
 * 0 иначе.
 *     Для знаковых типов __UNSIGNED_OF_##__TYPE должем быть определён как
 *     соответствующий беззнаковый тип большего или равного размера.
 *
 * __TYPE_HAS_EXTENSION должно быть определено как 1, если есть тип того же
 * знака, но хотя бы удвоенного размера (расширенный тип), 0 иначе.
 *     Для расширяемых типов __EXTENDED_OF_##__TYPE должен быть определён как
 *     соответствующий расширенный тип.
 *     Если __TYPE знаковый и расширяемый, то для __UNSIGNED_OF_##__TYPE также
 *     должен быть определён расширенный тип.
 */


#ifdef __TYPE
#ifdef __TYPE_IS_UNSIGNED
#ifdef __TYPE_HAS_EXTENSION

// Unsigned.
// Беззнаковый.
#if __TYPE_IS_UNSIGNED
    #if __TYPE_HAS_EXTENSION
        define_h_fxp_u__extended(__TYPE,__EXTENDED(__TYPE))
    #else
        define_h_fxp_u(__TYPE)
    #endif

// Signed.
// Знаковый.
#else
    #if __TYPE_HAS_EXTENSION
        define_h_fxp_s__extended(__TYPE,__EXTENDED(__TYPE),__UNSIGNED(__TYPE))
    #else
        define_h_fxp_s(__TYPE,__UNSIGNED(__TYPE))
    #endif
#endif

#endif
#endif
#endif
