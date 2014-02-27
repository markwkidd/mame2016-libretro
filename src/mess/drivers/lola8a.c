// license:MAME
// copyright-holders:Miodrag Milanovic, Robbbert
/***************************************************************************

        Lola 8A

        Ivo Lola Ribar Institute

        2013-08-28 Skeleton driver.


    BASIC commands :

    LET NEXT IF GOTO GOSUB RETURN READ DATA FOR CLS INPUT DIM STOP END RESTORE
    REM CLEAR PUSH POKE PRINT OUT ERROR USR CURSOR NORMAL INVERSE PLOT UNPLOT
    ELSE WIPE COLOUR CENTRE RANGE DRAW CIRCLE LOAD SAVE VERIFY HLOAD HSAVE HVERIFY
    DLOAD DSAVE DVERIFY MERGE CAT RUN NEW ON LIST DEF MON GWIND TWIND UNDER
    SPC OFF TAB THEN TO STEP AND OR XOR NOT ABS LEN SQR INT ASC CHR VAL STR MID
    ARG CALL RND LEFT RIGHT DOT SGN SIN FREE PI FN TAN COS POP PEEK INP LN EXP ATN
****************************************************************************/

#include "emu.h"
#include "cpu/i8085/i8085.h"
#include "video/mc6845.h"
#include "sound/ay8910.h"
#include "imagedev/cassette.h"
#include "sound/wave.h"

#define AY8910_TAG "g12"
#define HD46505SP_TAG "h45"


class lola8a_state : public driver_device
{
public:
	lola8a_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag)
		, m_maincpu(*this, "maincpu")
		, m_cass(*this, "cassette")
	{ }

	required_device<cpu_device> m_maincpu;

	DECLARE_PALETTE_INIT(lola8a);
	virtual void machine_reset() { m_maincpu->set_pc(0x8000); }

	DECLARE_READ8_MEMBER(lola8a_port_a_r);
	DECLARE_WRITE8_MEMBER(lola8a_port_b_w);
	DECLARE_WRITE_LINE_MEMBER(crtc_vsync);
	DECLARE_READ_LINE_MEMBER(cass_r);
	DECLARE_WRITE_LINE_MEMBER(cass_w);

	DECLARE_READ8_MEMBER(keyboard_r);

private:
	UINT8 m_portb;
	required_device<cassette_image_device> m_cass;
};

static ADDRESS_MAP_START(lola8a_mem, AS_PROGRAM, 8, lola8a_state)
	ADDRESS_MAP_UNMAP_HIGH
	AM_RANGE( 0x0000, 0x1fff ) AM_RAM // 6264 at G45
	AM_RANGE( 0x2000, 0x3fff ) AM_RAM // 6264 at F45
										// empty place for 6264 at E45
										// empty place for 6264 at D45
	AM_RANGE( 0x8000, 0x9fff ) AM_ROM // 2764A at B45
	AM_RANGE( 0xa000, 0xbfff ) AM_ROM // 2764A at C45
	AM_RANGE( 0xc000, 0xdfff ) AM_ROM // 2764A at H67
	AM_RANGE( 0xe000, 0xffff ) AM_RAM // 6264 at G67
ADDRESS_MAP_END

static ADDRESS_MAP_START(lola8a_io, AS_IO, 8, lola8a_state)
	ADDRESS_MAP_UNMAP_HIGH
	AM_RANGE(0x80, 0x80) AM_DEVWRITE(AY8910_TAG, ay8910_device, address_w)
	AM_RANGE(0x84, 0x84) AM_DEVREADWRITE(AY8910_TAG, ay8910_device, data_r, data_w)
	AM_RANGE(0x88, 0x88) AM_READ(keyboard_r)

	AM_RANGE(0x90, 0x90) AM_DEVREADWRITE(HD46505SP_TAG, mc6845_device, status_r, address_w)
	AM_RANGE(0x92, 0x92) AM_DEVREADWRITE(HD46505SP_TAG, mc6845_device, register_r, register_w)

ADDRESS_MAP_END

/* Input ports */
static INPUT_PORTS_START( lola8a )
	PORT_START("line_0")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_A)
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_LEFT)
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_1)
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_2)
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_Q)
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_CAPSLOCK)
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_LSHIFT) PORT_CODE(KEYCODE_RSHIFT)
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_LCONTROL) PORT_CODE(KEYCODE_RCONTROL)

	PORT_START("line_1")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_Z)
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_RIGHT)
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_3)
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_W)
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_S)
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_X)
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_LSHIFT) PORT_CODE(KEYCODE_RSHIFT)
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_LCONTROL) PORT_CODE(KEYCODE_RCONTROL)

	PORT_START("line_2")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_R)
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_F)
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_4)
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_E)
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_D)
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_C)
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_LSHIFT) PORT_CODE(KEYCODE_RSHIFT)
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_LCONTROL) PORT_CODE(KEYCODE_RCONTROL)

	PORT_START("line_3")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_V)
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_B)
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_5)
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_T)
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_G)
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_6)
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_LSHIFT) PORT_CODE(KEYCODE_RSHIFT)
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_LCONTROL) PORT_CODE(KEYCODE_RCONTROL)

	PORT_START("line_4")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_N)
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_SPACE)
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_7)
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_Y)
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_U)
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_H)
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_LSHIFT) PORT_CODE(KEYCODE_RSHIFT)
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_LCONTROL) PORT_CODE(KEYCODE_RCONTROL)

	PORT_START("line_5")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_M)
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_K)
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_8)
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_I)
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_J)
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_9)
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_LSHIFT) PORT_CODE(KEYCODE_RSHIFT)
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_LCONTROL) PORT_CODE(KEYCODE_RCONTROL)

	PORT_START("line_6")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_BACKSLASH)// Z"
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_COMMA)
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_0)
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_P)
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_L)
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_O)
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_LSHIFT) PORT_CODE(KEYCODE_RSHIFT)
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_LCONTROL) PORT_CODE(KEYCODE_RCONTROL)

	PORT_START("line_7")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_UNUSED) // C"
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_STOP)
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_MINUS) // =
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_UNUSED) // S"
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_UNUSED) // C'
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_UNUSED) // ;
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_LSHIFT) PORT_CODE(KEYCODE_RSHIFT)
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_LCONTROL) PORT_CODE(KEYCODE_RCONTROL)

	PORT_START("line_8")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_SLASH)// /
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_DOWN)
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_UNUSED) // ????
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_OPENBRACE)
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_UP)
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_UNUSED) // :
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_LSHIFT) PORT_CODE(KEYCODE_RSHIFT)
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_LCONTROL) PORT_CODE(KEYCODE_RCONTROL)

	PORT_START("line_9")
	PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_ENTER) // return
	PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_UNUSED) // ????
	PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_UNUSED) // ????
	PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_CLOSEBRACE)
	PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_UNUSED) // ????
	PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_TILDE)// @
	PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_LSHIFT) PORT_CODE(KEYCODE_RSHIFT)
	PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_CODE(KEYCODE_LCONTROL) PORT_CODE(KEYCODE_RCONTROL)
INPUT_PORTS_END


PALETTE_INIT_MEMBER(lola8a_state, lola8a)
{
	int i;

	for(i=0;i<8;i++) {
		palette.set_pen_color(i, pal1bit(i >> 1),pal1bit(i >> 2),pal1bit(i >> 0));
	}
}

static MC6845_UPDATE_ROW( lola8a_update_row )
{
	lola8a_state *state = device->machine().driver_data<lola8a_state>();
	address_space &program = state->m_maincpu->space(AS_PROGRAM);
	const rgb_t *palette = bitmap.palette()->entry_list_raw();

	for (int sx = 0; sx < x_count; sx++)
	{
		UINT16 addr = 0xa000 + sx*8 + ra + ma * 8;
		UINT8 code = program.read_byte(addr);

		for (int x = 0; x <= 8; x++)
		{
			int color = BIT(code, 7-x) ? 7 : 0;
			if (cursor_x==sx) color = 7;
			bitmap.pix32(y, x + sx*8) = palette[color];
		}
	}
}

READ8_MEMBER(lola8a_state::lola8a_port_a_r)
{
	logerror("lola8a_port_a_r\n");
	return 0x00;
}

WRITE8_MEMBER(lola8a_state::lola8a_port_b_w)
{
	m_portb = data;
}

READ_LINE_MEMBER( lola8a_state::cass_r )
{
	return (m_cass->input() < 0.03);
}

WRITE_LINE_MEMBER( lola8a_state::cass_w )
{
	m_cass->output(state ? -1.0 : +1.0);
}

READ8_MEMBER(lola8a_state::keyboard_r)
{
	static const char *const keynames[] =
	{
		"line_0", "line_1", "line_2", "line_3",
		"line_4", "line_5", "line_6", "line_7",
		"line_8", "line_9", NULL, NULL,
		NULL,NULL,NULL,NULL
	};

	if( keynames[m_portb & 0x0f])
		return ioport(keynames[m_portb & 0x0f])->read();
	return 0xff;
}

WRITE_LINE_MEMBER(lola8a_state::crtc_vsync)
{
	m_maincpu->set_input_line(I8085_RST75_LINE, state? ASSERT_LINE : CLEAR_LINE);
}

static MC6845_INTERFACE( hd46505sp_intf )
{
	false,
	0,0,0,0,
	8,
	NULL,
	lola8a_update_row,
	NULL,
	DEVCB_NULL,
	DEVCB_NULL,
	DEVCB_NULL,
	DEVCB_DRIVER_LINE_MEMBER(lola8a_state, crtc_vsync),
	NULL
};

static const ay8910_interface psg_intf =
{
	AY8910_LEGACY_OUTPUT,
	AY8910_DEFAULT_LOADS,
	DEVCB_DRIVER_MEMBER(lola8a_state, lola8a_port_a_r),
	DEVCB_NULL,
	DEVCB_NULL,
	DEVCB_DRIVER_MEMBER(lola8a_state, lola8a_port_b_w)
};

static MACHINE_CONFIG_START( lola8a, lola8a_state )
	/* basic machine hardware */
	MCFG_CPU_ADD("maincpu", I8085A, XTAL_4_9152MHz)
	MCFG_CPU_PROGRAM_MAP(lola8a_mem)
	MCFG_CPU_IO_MAP(lola8a_io)
	MCFG_I8085A_SID(READLINE(lola8a_state, cass_r))
	MCFG_I8085A_SOD(WRITELINE(lola8a_state, cass_w))

	MCFG_SPEAKER_STANDARD_MONO("mono")
	MCFG_SOUND_ADD(AY8910_TAG, AY8910, XTAL_4_9152MHz / 4)
	MCFG_SOUND_CONFIG(psg_intf)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS,"mono",1.0)

	/* video hardware */
	MCFG_SCREEN_ADD("screen", RASTER)
	MCFG_SCREEN_REFRESH_RATE(50)
	MCFG_SCREEN_VBLANK_TIME(ATTOSECONDS_IN_USEC(2500)) /* not accurate */
	MCFG_SCREEN_UPDATE_DEVICE(HD46505SP_TAG, hd6845_device, screen_update)
	MCFG_SCREEN_SIZE(640, 480)
	MCFG_SCREEN_VISIBLE_AREA(0, 640-1, 0, 480-1)
	MCFG_MC6845_ADD(HD46505SP_TAG, HD6845, "screen", XTAL_8MHz / 8, hd46505sp_intf) // HD6845 == HD46505S
	MCFG_PALETTE_ADD("palette", 8)
	MCFG_PALETTE_INIT_OWNER(lola8a_state, lola8a)

	/* Cassette */
	MCFG_CASSETTE_ADD( "cassette", default_cassette_interface )
	MCFG_SOUND_WAVE_ADD(WAVE_TAG, "cassette")
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.25)
MACHINE_CONFIG_END

/* ROM definition */
ROM_START( lola8a )
	ROM_REGION( 0x10000, "maincpu", ROMREGION_ERASEFF )
	ROM_LOAD( "lola 8a r0 w06 22.11.86.b45", 0x8000, 0x2000, CRC(aca1fc08) SHA1(f7076d937bb53b0addcba2a5b7c05ab75d6d0d93))
	ROM_LOAD( "lola 8a r1 w06 22.11.86.c45", 0xa000, 0x2000, CRC(99f8ec9b) SHA1(88eafd09c479f177525fa0039cf04d74bae39dab))
	ROM_LOAD( "lola 8a r2 w06 22.11.86.h67", 0xc000, 0x2000, CRC(1e7cd46b) SHA1(048b2583ee7baeb9621e629b79ed64583ac5d554))
ROM_END

/* Driver */

/*    YEAR  NAME    PARENT  COMPAT   MACHINE    INPUT    CLASS          INIT    COMPANY   FULLNAME       FLAGS */
COMP( 1986, lola8a,  0,       0,    lola8a,     lola8a,  driver_device,  0,      "Institut Ivo Lola Ribar",   "Lola 8A",        GAME_NOT_WORKING)
