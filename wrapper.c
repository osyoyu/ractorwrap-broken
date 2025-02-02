#include <ruby.h>
#include <ruby/ractor.h>

static VALUE rb_cRactorWrap;

struct ractor_wrap {
    VALUE ractor;
};

static void ractor_wrap_mark(void *ptr) {
    struct ractor_wrap *wrap = (struct ractor_wrap *)ptr;
    rb_gc_mark(wrap->ractor);
}

static void ractor_wrap_free(void *ptr) {
    xfree(ptr);
}

static size_t ractor_wrap_memsize(const void *ptr) {
    return sizeof(struct ractor_wrap);
}

static const rb_data_type_t ractor_wrap_type = {
    .wrap_struct_name = "RactorWrap",
    .function = {
        .dmark = ractor_wrap_mark,
        .dfree = ractor_wrap_free,
        .dsize = ractor_wrap_memsize,
    },
    .flags = RUBY_TYPED_FREE_IMMEDIATELY | RUBY_TYPED_WB_PROTECTED | RUBY_TYPED_FROZEN_SHAREABLE
};

static VALUE ractor_wrap_alloc(VALUE klass) {
    struct ractor_wrap *wrap;
    VALUE obj = TypedData_Make_Struct(klass, struct ractor_wrap, &ractor_wrap_type, wrap);
    return obj;
}

void Init_wrapper(void) {
    rb_cRactorWrap = rb_define_class("RactorWrap", rb_cObject);
    rb_define_alloc_func(rb_cRactorWrap, ractor_wrap_alloc);
}
