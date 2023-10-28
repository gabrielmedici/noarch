#pragma once

#include "Windows.h"
#include "filesystem"
#include "godot_cpp/classes/object.hpp"
#include "libretro.h"
#include "godot_cpp/classes/image.hpp"

class RetroHost : public godot::Object
{
    GDCLASS( RetroHost, godot::Object )

public:
    godot::String cwd;
    static RetroHost* get_singleton();

    RetroHost();
    ~RetroHost();

    bool load_core( godot::String path );
    void unload_core();
    void run();

private:

    static RetroHost* singleton;

    bool core_environment(unsigned cmd, void *data);

    void core_video_init( const struct retro_game_geometry *geometry );
    void core_video_refresh(const void *data, unsigned width, unsigned height, size_t pitch);
    bool core_video_set_pixel_format( unsigned format );
    godot::Image::Format pixel_format;

    void core_input_poll(void);
    int16_t core_input_state(unsigned port, unsigned device, unsigned index, unsigned id);

    void core_audio_init( retro_system_av_info av );
    void core_audio_sample(int16_t left, int16_t right);
    size_t core_audio_sample_batch(const int16_t *data, size_t frames);

    struct
    {
        HINSTANCE handle;
        bool initialized = false;

        void ( *retro_init )( void );
        void ( *retro_deinit )( void );
        unsigned ( *retro_api_version )( void );
        void ( *retro_get_system_info )( struct retro_system_info *info );
        void ( *retro_get_system_av_info )( struct retro_system_av_info *info );
        void ( *retro_set_controller_port_device )( unsigned port, unsigned device );
        void ( *retro_reset )( void );
        void ( *retro_run )( void );
        // size_t retro_serialize_size(void);
        // bool retro_serialize(void *data, size_t size);
        // bool retro_unserialize(const void *data, size_t size);
        // void retro_cheat_reset(void);
        // void retro_cheat_set(unsigned index, bool enabled, const char *code);
        bool ( *retro_load_game )( const struct retro_game_info *game );
        // bool retro_load_game_special(
        //   unsigned game_type,
        //   const struct retro_game_info *info,
        //   size_t num_info);
        void ( *retro_unload_game )( void );
        // unsigned retro_get_region(void);
        // void *retro_get_memory_data(unsigned id);
        // size_t retro_get_memory_size(unsigned id);
    } core;

protected:
    static void _bind_methods();
};