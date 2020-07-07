#ifndef TEMPLATES_H
#define TEMPLATES_H

/*
 * C macro-based templates realisation.
 *
 * Реализация шаблонов в Си при помощи макросов.
 */

// Было бы неплохо еще иметь шаблоны для макросов... :)
#define CAT_2(X1,X2)       X1##_##X2
#define CAT_3(X1,X2,X3)    X1##_##X2##_##X3
#define CAT_4(X1,X2,X3,X4) X1##_##X2##_##X3##_##X4

#define TEMPLATE_2(X1,X2)       CAT_2(X1,X2)
#define TEMPLATE_3(X1,X2,X3)    CAT_3(X1,X2,X3)
#define TEMPLATE_4(X1,X2,X3,X4) CAT_4(X1,X2,X3,X4)

#endif
