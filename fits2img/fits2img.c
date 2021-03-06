/* This file is part of the PROBA2 Science Operations Center software.
 * Copyright (C) 2007-2014 Royal Observatory of Belgium.
 * For copying permission, see the file COPYING in the distribution.
 *
 * Author: Bogdan Nicula
 */

static const char _versionid_[] __attribute__ ((unused)) =
    "$Id: fits2img.c 2636 2014-11-21 18:22:17Z bogdan $";

#include <string.h>
#include <glib.h>

#include "p2sc_name.h"
#include "p2sc_stdlib.h"

#include "swap_color.h"
#include "swap_file.h"
#include "swap_file_j2k.h"
#include "swap_qlook.h"

#include "fitsproc.h"

#define APP_NAME "SWHV"

#define DEF_CLIP_MIN     0
#define DEF_CLIP_MAX     8191
#define DEF_GAMMA        2.2
#define DEF_CRATIO       3.3
#define DEF_NLAYERS      4
#define DEF_NRESOLUTIONS 6
#define DEF_PRECINCTW    128
#define DEF_PRECINCTH    128

int main(int argc, char **argv)
{
    int datedir = 0, noverify = 0, jhv = 0, debug = 0;
    char *appname = NULL, *outdir = NULL, *cm = NULL, *func = NULL;

    double clipmin = DEF_CLIP_MIN, clipmax = DEF_CLIP_MAX;
    double gamma = DEF_GAMMA, cratio = DEF_CRATIO;
    int nlayers = DEF_NLAYERS, nresolutions = DEF_NRESOLUTIONS;
    int precinctw = DEF_PRECINCTW, precincth = DEF_PRECINCTH;

    GOptionEntry entries[] = {
        {"appname", 'a', 0, G_OPTION_ARG_STRING, &appname,
         "Present to LMAT other appname than " APP_NAME, APP_NAME},
        {"out-dir", 'o', 0, G_OPTION_ARG_STRING, &outdir,
         "Output directory", "name"},
        {"out-dateobs-dir", 'O', 0, G_OPTION_ARG_NONE, &datedir,
         "Use the date of observation for the output directory name", NULL},
        {"function", 'f', 0, G_OPTION_ARG_STRING, &func,
         "Pixel transfer function: gamma, log", "gamma"},
        {"gamma", 'g', 0, G_OPTION_ARG_DOUBLE, &gamma,
         "Gamma correction exponent", G_STRINGIFY(DEF_GAMMA)},
        {"min-clip", 'm', 0, G_OPTION_ARG_DOUBLE, &clipmin,
         "Clip lower pixel values", G_STRINGIFY(DEF_CLIP_MIN)},
        {"max-clip", 'M', 0, G_OPTION_ARG_DOUBLE, &clipmax,
         "Clip higher pixel values", G_STRINGIFY(DEF_CLIP_MAX)},
        {"jhv", 'J', 0, G_OPTION_ARG_NONE, &jhv,
         "Output a file suitable for use with Helioviewer", NULL},
        {"cratio", 0, 0, G_OPTION_ARG_DOUBLE, &cratio,
         "OpenJPEG compression ratio", G_STRINGIFY(DEF_CRATIO)},
        {"nlayers", 0, 0, G_OPTION_ARG_INT, &nlayers,
         "OpenJPEG number of layers", G_STRINGIFY(DEF_NLAYERS)},
        {"nresolutions", 0, 0, G_OPTION_ARG_INT, &nresolutions,
         "OpenJPEG number of resolutions", G_STRINGIFY(DEF_NRESOLUTIONS)},
        {"precinctw", 0, 0, G_OPTION_ARG_INT, &precinctw,
         "OpenJPEG precinct width", G_STRINGIFY(DEF_PRECINCTW)},
        {"precincth", 0, 0, G_OPTION_ARG_INT, &precincth,
         "OpenJPEG precinct height", G_STRINGIFY(DEF_PRECINCTH)},
        {"debug", 0, 0, G_OPTION_ARG_NONE, &debug,
         "OpenJPEG debug mode", NULL},
        {"colormap", 'C', 0, G_OPTION_ARG_STRING, &cm,
         "Use a colormap: hot, jet, aia171", "name"},
        {"no-verify", 'N', 0, G_OPTION_ARG_NONE, &noverify,
         "Do not verify FITS checksums", NULL},
        {NULL, 0, 0, G_OPTION_ARG_NONE, NULL, NULL, NULL}
    };

    p2sc_option(argc, argv, APP_NAME, "FILE - SWAP Media Product Generator",
                "This program generates quicklook images out of FITS files",
                entries);
    if (appname) {
        p2sc_set_string("appname", appname);
        g_free(appname);
    }

    procfits_t *p = fitsproc(argv[1], noverify);

    guint8 *g;
    swap_crispen(p->im, p->w, p->h);
    if (func && !strcmp(func, "log"))
        g = swap_xfer_log(p->im, p->w, p->h, clipmin, clipmax);
    else
        g = swap_xfer_gamma(p->im, p->w, p->h, clipmin, clipmax, gamma);
    g_free(func);

    if (datedir) {
        char *od = outdir;
        outdir = p2sc_name_dirtree(outdir, p->dateobs);
        g_free(od);
    }

    char *name;
    if (jhv) {
        char *jhvname = p2sc_name_swap_jhv(p->dateobs, p->telescop, p->instrume,
                                           p->detector, p->wavelnth);
        name = p2sc_name_swap_qlk(outdir, jhvname, "jp2");

        swap_j2kparams_t j2kp = {
            .cratio = cratio,
            .nlayers = nlayers,
            .nresolutions = nresolutions,
            .precinct = {precinctw, precincth},
            .meta = {
                     .xml = p->xml,
                     .pal = cm ?
                     swap_palette_rgb_get(cm) : swap_palette_rgb_get("aia171")
                     },
            .debug = debug
        };
        swap_write_j2k(name, g, p->w, p->h, &j2kp);

        g_free(jhvname);
    } else {
        name = p2sc_name_swap_qlk(outdir, p->name, "png");
        swap_write_png(name, g, p->w, p->h, swap_palette_rgb_get(cm));
    }
    g_free(name);

    g_free(g);
    procfits_free(p);

    g_free(cm);
    g_free(outdir);

    return 0;
}
