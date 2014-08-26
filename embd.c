#include "scheme.h"
#include "base.c"


static int run(Scheme_Env *e, int argc, char *argv[])
{
  Scheme_Object *curout = NULL, *v = NULL, *a[2] = {NULL, NULL};
  Scheme_Config *config = NULL;
  int i;
  mz_jmp_buf * volatile save = NULL, fresh;
  
  MZ_GC_DECL_REG(8);
  MZ_GC_VAR_IN_REG(0, e);
  MZ_GC_VAR_IN_REG(1, curout);
  MZ_GC_VAR_IN_REG(2, save);
  MZ_GC_VAR_IN_REG(3, config);
  MZ_GC_VAR_IN_REG(4, v);
  MZ_GC_ARRAY_VAR_IN_REG(5, a, 2);
  
  MZ_GC_REG();
  
  declare_modules(e);
  
  v = scheme_intern_symbol("racket/base");
  scheme_namespace_require(v);
  
  config = scheme_current_config();
  curout = scheme_get_param(config, MZCONFIG_OUTPUT_PORT);
  v = scheme_make_char('\n');
  scheme_display(v, curout);
  /* read-eval-print loop, uses initial Scheme_Env: */
  a[0] = scheme_intern_symbol("racket/base");
  a[1] = scheme_intern_symbol("read-eval-print-loop");
  v = scheme_dynamic_require(2, a);
  scheme_apply(v, 0, NULL);
  scheme_current_thread->error_buf = save;
  MZ_GC_UNREG();
  
  return 0;
}

#if defined(WIN32) && defined(USE_THREAD_LOCAL)
static __declspec(thread) void *tls_space;
#endif

int main(int argc, char *argv[])
{
#if defined(WIN32) && defined(USE_THREAD_LOCAL)
	scheme_register_tls_space(&tls_space, 0);
#endif
	return scheme_main_setup(1, run, argc, argv);
}
