#ifndef _JK_SPINNER_EO_H_
#define _JK_SPINNER_EO_H_

#ifndef _JK_SPINNER_EO_CLASS_TYPE
#define _JK_SPINNER_EO_CLASS_TYPE

typedef Eo Jk_Spinner;

#endif

#ifndef _JK_SPINNER_EO_TYPES
#define _JK_SPINNER_EO_TYPES


#endif
#define JK_SPINNER_CLASS jk_spinner_class_get()

EWAPI const Eo_Class *jk_spinner_class_get(void);

/**
 * @brief Control whether the spinner should wrap when it reaches its minimum
 * or maximum value.
 *
 * Disabled by default. If disabled, when the user tries to increment the
 * value, but displayed value plus step value is bigger than maximum value, the
 * new value will be the maximum value. The same happens when the user tries to
 * decrement it, but the value less step is less than minimum value. In this
 * case, the new displayed value will be the minimum value.
 *
 * When wrap is enabled, when the user tries to increment the value, but
 * displayed value plus step value is bigger than maximum value, the new value
 * will be the minimum value. When the the user tries to decrement it, but the
 * value less step is less than minimum value, the new displayed value will be
 * the maximum value.
 *
 * E.g.: @c min = 10 @c max = 50 @c step = 20 @c displayed = 20
 *
 * When the user decrement value (using left or bottom arrow), it will displays
 * $50.
 *
 * @param[in] wrap @c true to enable wrap or @c false to disable it.
 *
 * @ingroup Jk_Spinner
 */
EOAPI void jk_obj_spinner_wrap_set(Eo *obj, Eina_Bool wrap);

/**
 * @brief Control whether the spinner should wrap when it reaches its minimum
 * or maximum value.
 *
 * Disabled by default. If disabled, when the user tries to increment the
 * value, but displayed value plus step value is bigger than maximum value, the
 * new value will be the maximum value. The same happens when the user tries to
 * decrement it, but the value less step is less than minimum value. In this
 * case, the new displayed value will be the minimum value.
 *
 * When wrap is enabled, when the user tries to increment the value, but
 * displayed value plus step value is bigger than maximum value, the new value
 * will be the minimum value. When the the user tries to decrement it, but the
 * value less step is less than minimum value, the new displayed value will be
 * the maximum value.
 *
 * E.g.: @c min = 10 @c max = 50 @c step = 20 @c displayed = 20
 *
 * When the user decrement value (using left or bottom arrow), it will displays
 * $50.
 *
 * @return @c true to enable wrap or @c false to disable it.
 *
 * @ingroup Jk_Spinner
 */
EOAPI Eina_Bool jk_obj_spinner_wrap_get(const Eo *obj);

/**
 * @brief Control the round value for rounding
 *
 * Sets the rounding value used for value rounding in the spinner.
 *
 * @param[in] rnd The rounding value
 *
 * @ingroup Jk_Spinner
 */
EOAPI void jk_obj_spinner_round_set(Eo *obj, int rnd);

/**
 * @brief Control the round value for rounding
 *
 * Sets the rounding value used for value rounding in the spinner.
 *
 * @return The rounding value
 *
 * @ingroup Jk_Spinner
 */
EOAPI int jk_obj_spinner_round_get(const Eo *obj);

/**
 * @brief Control whether the spinner can be directly edited by the user or
 * not.
 *
 * Spinner objects can have edition disabled, in which state they will be
 * changed only by arrows. Useful for contexts where you don't want your users
 * to interact with it writing the value. Specially when using special values,
 * the user can see real value instead of special label on edition.
 *
 * It's enabled by default.
 *
 * @param[in] editable @c true to allow users to edit it or @c false to don't
 * allow users to edit it directly.
 *
 * @ingroup Jk_Spinner
 */
EOAPI void jk_obj_spinner_editable_set(Eo *obj, Eina_Bool editable);

/**
 * @brief Control whether the spinner can be directly edited by the user or
 * not.
 *
 * Spinner objects can have edition disabled, in which state they will be
 * changed only by arrows. Useful for contexts where you don't want your users
 * to interact with it writing the value. Specially when using special values,
 * the user can see real value instead of special label on edition.
 *
 * It's enabled by default.
 *
 * @return @c true to allow users to edit it or @c false to don't allow users
 * to edit it directly.
 *
 * @ingroup Jk_Spinner
 */
EOAPI Eina_Bool jk_obj_spinner_editable_get(const Eo *obj);

/**
 * @brief Control the base for rounding
 *
 * Rounding works as follows:
 *
 * rounded_val = base + (double)(((value - base) / round) * round)
 *
 * Where rounded_val, value and base are doubles, and round is an integer.
 *
 * This means that things will be rounded to increments (or decrements) of
 * "round" starting from value @c base. The default base for rounding is 0.
 *
 * Example: round = 3, base = 2 Values: ..., -2, 0, 2, 5, 8, 11, 14, ...
 *
 * Example: round = 2, base = 5.5 Values: ..., -0.5, 1.5, 3.5, 5.5, 7.5, 9.5,
 * 11.5, ...
 *
 * @param[in] base The base value
 *
 * @ingroup Jk_Spinner
 */
EOAPI void jk_obj_spinner_base_set(Eo *obj, double base);

/**
 * @brief Control the base for rounding
 *
 * Rounding works as follows:
 *
 * rounded_val = base + (double)(((value - base) / round) * round)
 *
 * Where rounded_val, value and base are doubles, and round is an integer.
 *
 * This means that things will be rounded to increments (or decrements) of
 * "round" starting from value @c base. The default base for rounding is 0.
 *
 * Example: round = 3, base = 2 Values: ..., -2, 0, 2, 5, 8, 11, 14, ...
 *
 * Example: round = 2, base = 5.5 Values: ..., -0.5, 1.5, 3.5, 5.5, 7.5, 9.5,
 * 11.5, ...
 *
 * @return The base value
 *
 * @ingroup Jk_Spinner
 */
EOAPI double jk_obj_spinner_base_get(const Eo *obj);

/**
 * @brief Control the format string of the displayed label.
 *
 * If @c NULL, this sets the format to "%.0f". If not it sets the format string
 * for the label text. The label text is provided a floating point value, so
 * the label text can display up to 1 floating point value. Note that this is
 * optional.
 *
 * Use a format string such as "%1.2f meters" for example, and it will display
 * values like: "3.14 meters" for a value equal to 3.14159.
 *
 * Default is "%0.f".
 *
 * @param[in] fmt The format string for the label display.
 *
 * @ingroup Jk_Spinner
 */
EOAPI void jk_obj_spinner_label_format_set(Eo *obj, const char *fmt);

/**
 * @brief Control the format string of the displayed label.
 *
 * If @c NULL, this sets the format to "%.0f". If not it sets the format string
 * for the label text. The label text is provided a floating point value, so
 * the label text can display up to 1 floating point value. Note that this is
 * optional.
 *
 * Use a format string such as "%1.2f meters" for example, and it will display
 * values like: "3.14 meters" for a value equal to 3.14159.
 *
 * Default is "%0.f".
 *
 * @return The format string for the label display.
 *
 * @ingroup Jk_Spinner
 */
EOAPI const char *jk_obj_spinner_label_format_get(const Eo *obj);

/**
 * @brief Control special string to display in the place of the numerical
 * value.
 *
 * It's useful for cases when a user should select an item that is better
 * indicated by a label than a value. For example, weekdays or months.
 *
 * @note If another label was previously set to @c value, it will be replaced
 * by the new label.
 *
 * @param[in] value The value to be replaced.
 * @param[in] label The label to be used.
 *
 * @ingroup Jk_Spinner
 */
EOAPI void jk_obj_spinner_special_value_add(Eo *obj, double value, const char *label);

EOAPI extern const Eo_Event_Description _JK_SPINNER_EVENT_CHANGED;
EOAPI extern const Eo_Event_Description _JK_SPINNER_EVENT_DELAY_CHANGED;
EOAPI extern const Eo_Event_Description _JK_SPINNER_EVENT_SPINNER_DRAG_START;
EOAPI extern const Eo_Event_Description _JK_SPINNER_EVENT_SPINNER_DRAG_STOP;

/**
 * No description
 */
#define JK_SPINNER_EVENT_CHANGED (&(_JK_SPINNER_EVENT_CHANGED))

/**
 * No description
 */
#define JK_SPINNER_EVENT_DELAY_CHANGED (&(_JK_SPINNER_EVENT_DELAY_CHANGED))

/**
 * No description
 */
#define JK_SPINNER_EVENT_SPINNER_DRAG_START (&(_JK_SPINNER_EVENT_SPINNER_DRAG_START))

/**
 * No description
 */
#define JK_SPINNER_EVENT_SPINNER_DRAG_STOP (&(_JK_SPINNER_EVENT_SPINNER_DRAG_STOP))

#endif
