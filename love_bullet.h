// Libraries
#ifdef _WIN32
#define TEST_EXPORT __declspec (dllexport)
#else
#define TEST_EXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif
TEST_EXPORT int luaopen_love_bullet(struct lua_State * L);
#ifdef __cplusplus
}
#endif