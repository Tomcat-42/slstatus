/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
const unsigned int interval = 1000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "";

/* maximum output string length */
#define MAXLEN 2048

/*
 * function            description                     argument (example)
 *
 * battery_perc        battery percentage              battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_state       battery charging state          battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_remaining   battery remaining HH:MM         battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * cpu_perc            cpu usage in percent            NULL
 * cpu_freq            cpu frequency in MHz            NULL
 * datetime            date and time                   format string (%F %T)
 * disk_free           free disk space in GB           mountpoint path (/)
 * disk_perc           disk usage in percent           mountpoint path (/)
 * disk_total          total disk space in GB          mountpoint path (/")
 * disk_used           used disk space in GB           mountpoint path (/)
 * entropy             available entropy               NULL
 * gid                 GID of current user             NULL
 * hostname            hostname                        NULL
 * ipv4                IPv4 address                    interface name (eth0)
 * ipv6                IPv6 address                    interface name (eth0)
 * kernel_release      `uname -r`                      NULL
 * keyboard_indicators caps/num lock indicators        format string (c?n?)
 *                                                     see keyboard_indicators.c
 * keymap              layout (variant) of current     NULL
 *                     keymap
 * load_avg            load average                    NULL
 * netspeed_rx         receive network speed           interface name (wlan0)
 * netspeed_tx         transfer network speed          interface name (wlan0)
 * num_files           number of files in a directory  path
 *                                                     (/home/foo/Inbox/cur)
 * ram_free            free memory in GB               NULL
 * ram_perc            memory usage in percent         NULL
 * ram_total           total memory size in GB         NULL
 * ram_used            used memory in GB               NULL
 * run_command         custom shell command            command (echo foo)
 * separator           string to echo                  NULL
 * swap_free           free swap in GB                 NULL
 * swap_perc           swap usage in percent           NULL
 * swap_total          total swap size in GB           NULL
 * swap_used           used swap in GB                 NULL
 * temp                temperature in degree celsius   sensor file
 *                                                     (/sys/class/thermal/...)
 *                                                     NULL on OpenBSD
 *                                                     thermal zone on FreeBSD
 *                                                     (tz0, tz1, etc.)
 * uid                 UID of current user             NULL
 * uptime              system uptime                   NULL
 * username            username of current user        NULL
 * vol_perc            OSS/ALSA volume in percent      mixer file (/dev/mixer)
 *                                                     NULL on OpenBSD
 * wifi_perc           WiFi signal in percent          interface name (wlan0)
 * wifi_essid          WiFi ESSID                      interface name (wlan0)
 *
 * media_mpd_stat          current_song time paused        NULL
 */
static const struct arg args[] = {
	/* function format          argument */
  {separator, "^b#000000^^c#ff004d^ ??? ", NULL},
  /* { media_mpd_stat,       "%s ",          NULL}, */
  { run_command,       "%s ",          "~/scripts/mpd-status&"},
  {separator, "^b#000000^^c#00e756^ ??? ", NULL},
  {cpu_perc,            " %s%% ",            NULL},
  {cpu_freq,            " %shz ",            NULL},
  {separator, "^b#000000^^c#fff024^ ??? ", NULL},
  {ram_perc,            "%s%% ",            NULL},
  {ram_used,            "%s ",            NULL},
  {separator, "^b#000000^^c#83769c^ ??? ", NULL},
  {temp,            "%s?? ",            "/sys/class/hwmon/hwmon5/temp1_input"},
  {separator, "^b#000000^^c#ff77a8^ ??? ", NULL},
  /* {wifi_essid,            " %s",            "wlp3s0"}, */
  /* {wifi_perc,            " %s%%",            "wlp3s0"}, */
  {ipv4,            " %s",            "wlan0"},
  {netspeed_rx, " ??? %s", "wlan0"},
  {netspeed_tx, " ??? %s ", "wlan0"},
  {separator, "^b#000000^^c#29adff^ ??? ", NULL},
  {ipv4,            " %s",            "eth0"},
  {netspeed_rx, " ??? %s", "eth0"},
  {netspeed_tx, " ??? %s ", "eth0"},
  {separator, "^b#000000^^c#ffffff^ ???  ", NULL},
  /* {disk_perc, " %s%% ", "/"}, */
  {disk_free, "%s ", "/"},
  /* {disk_perc, "%s%% ", "/mnt/PABLO"}, */
  {disk_free, "%s ", "/mnt/data"},
  {separator, "^b#000000^^c#ff004d^ ???  ", NULL},
  { datetime, "%s ",           "%d/%m/%y %T" },
  {separator, "^b#000000^^c#00e756^ ", NULL},
  { run_command,  "%s ",              "$(pamixer --get-mute) && echo ???  || echo ??? " },
	{ run_command,  " %s%% ",       "pamixer --get-volume" },
  {separator, "^c#fff024^^b#000000^ ???  ", NULL},
  {battery_perc, "%s", "BAT0"},
  {battery_state, "%s ", "BAT0"},
  {battery_perc, "%s", "BAT1"},
  {battery_state, "%s ", "BAT1"},
	{ run_command,  " %s ",       "cat /tmp/dwmbuf" },
};
