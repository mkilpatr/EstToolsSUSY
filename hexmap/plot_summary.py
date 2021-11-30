import os, sys, glob

import pandas as pd
import numpy as np
from argparse import ArgumentParser
import uproot
import json

import matplotlib as mpl
import matplotlib.pyplot as plt
from matplotlib.patches import RegularPolygon, Rectangle
from matplotlib.collections import PatchCollection
from matplotlib.legend_handler import HandlerPatch

font = {"size": 20}
mpl.rc("font", **font)

##### Mapping functions

# To get the pad number from the chip, channel number and channel type
# map_dict: a dictionary containing the pad - channel mapping from corresponding file
# chip: chip number
# chan: channel number
# chantype: channel type (0 for normal, 1 for calib or 100 for CM)
def get_pad_id(map_dict, chan, chantype, location, which): 
    if (chan, chantype, location, which) in map_dict["PAD"]:
        return map_dict["PAD"][(chan, chantype, location, which)]
    else:
        return 0

# To get channel number for measured points
def location_to_pad(name = "Center", ibin = 0):
    Center = [88]
    Corner = [1, 8, 18, 95, 111, 189, 197, 191, 190, 96, 81, 9]
    Edge = [3, 5, 39, 65, 140, 168, 195, 193, 169, 141, 52, 29] if args.testType == "" else [4, 51, 155, 194, 156, 40]
    Middle = [22, 24, 37, 78, 123, 151, 164, 160, 159, 115, 68, 42]
    Point = [58, 76, 121, 133, 117, 71]

    if name == "Center": return Center[ibin]
    elif name == "Corner": return Corner[ibin]
    elif name == "Edges": return Edge[ibin]
    elif name == "Middle": return Middle[ibin]
    elif name == "Point": return Point[ibin]
    
# To add the pad - channel and geometry mapping to the data DataFrame
# df: pandas DataFrame with the data
# hb_type: the type of the board ("LD" for low density or "HD" for high density)
def add_mapping(df, hb_type = "LD", module = "module812"):
    # create dataFrame clone to avoid conflict
    df_data = df 
    s = ""
    if not os.getcwd().endswith('hexmap'):
        s = 'hexmap/' 
    # geometry mapping files' paths
    ld_board_geo = s + "geometries/hex_positions_HPK_198ch_8inch_edge_ring_testcap.txt"
    hd_board_geo = s + "geometries/hex_positions_HPK_432ch_8inch_edge_ring_testcap.txt"

    # pad - channel mapping files' paths
    ld_board_chan = s + "channel_maps/ld_pad_to_channel_mapping_heightMaps.csv"
    if args.testType != "": ld_board_chan = s + "channel_maps/ld_pad_to_channel_mapping_heightMaps_OGP.csv"
    hd_board_chan = s + "channel_maps/hd_pad_to_channel_mapping.csv"

    # import mapping files to pandas dataFrames and transform to python dicts
    if hb_type == "LD":
        chan_map_fname = ld_board_chan
        geo_fname = ld_board_geo
    elif hb_type == "HD":
        chan_map_fname = hd_board_chan
        geo_fname = hd_board_geo

    df_ch_map = pd.read_csv(chan_map_fname)
    d_ch_map = df_ch_map.set_index(["Channel", "Channeltype", "Location", "Which"]).to_dict()

    df_pad_map = pd.read_csv(geo_fname, skiprows= 7, delim_whitespace=True, names = ['padnumber', 'xposition', 'yposition', 'type', 'optional'])
    df_pad_map = df_pad_map[["padnumber","xposition","yposition"]].set_index("padnumber")
    d_pad_map = df_pad_map.to_dict()

    # add mapping to the data dataFrames
    print(df_data)

    #df_data["pad"] = df_data.apply(lambda x: get_pad_id(d_ch_map, int(x.module812.Channel[0]), x.module812.Channeltype, x.module812.location, x.module812.which), axis = 1)
    df_data[module]["x"] = pd.Series(df_data[module]["Pad"]).map(d_pad_map["xposition"])
    df_data[module]["y"] = pd.Series(df_data[module]["Pad"]).map(d_pad_map["yposition"])

    return df_data

##### Plotting functions

# To plot the patches
# df: pandas DataFrame with the data
# mask: a mask to select specific data from the dataframe (eg. df['Channeltype'] == 0)
# data_type: the type of data corresponding to the mask ('norm' for normal, 'calib' for calib, 
#                                             'cm0' for CM of type 0, 'cm1' for CM of type 1 or 'nc' for not connected)
# hb_type: the type of the board ("LD" for low density or "HD" for high density)
def create_patches(df, mask, data_type, hb_type = "LD"):
    patches = []
    local_mask = mask.copy()
    r = 0.43
    if hb_type == "HD":
        r = 0.28
    for x, y in df.loc[local_mask, ["x", "y"]].values:
        angle = 0
        edgec = None
        if data_type == 'norm':
            ver = 6
            rad = r
        elif data_type == 'calib':
            ver = 6
            rad = 0.5 * r
            edgec = 'black'
        elif data_type == 'cm0':
            ver = 5
            rad = 0.75 * r
        elif data_type == 'cm1':
            ver = 4
            rad = 0.85 * r
            angle = np.radians(45)
        elif data_type == 'nc':
            ver = 100
            rad = 0.75 * r
        patch = RegularPolygon((x, y), numVertices = ver, radius = rad, orientation = angle, edgecolor = edgec, alpha = 0.9)
        patches.append(patch)
    return patches

# Classes to create the legend
class HandlerHexagon(HandlerPatch):
    def create_artists(self, legend, orig_handle,
                       xdescent, ydescent, width, height, fontsize, trans):
        center = 0.5 * width - 0.5 * xdescent, 0.5 * height - 0.5 * ydescent
        p = RegularPolygon(xy=center, numVertices = 6, radius = 10, orientation=0, edgecolor = 'k')
        self.update_prop(p, orig_handle, legend)
        p.set_transform(trans)
        return [p]
class HandlerPentagon(HandlerPatch):
    def create_artists(self, legend, orig_handle,
                       xdescent, ydescent, width, height, fontsize, trans):
        center = 0.5 * width - 0.5 * xdescent, 0.5 * height - 0.5 * ydescent
        p = RegularPolygon(xy=center, numVertices = 5, radius = 10, orientation=0)
        self.update_prop(p, orig_handle, legend)
        p.set_transform(trans)
        return [p] 
class HandlerSquare(HandlerPatch):
    def create_artists(self, legend, orig_handle,
                       xdescent, ydescent, width, height, fontsize, trans):
        center = 0.5 * width - 0.5 * xdescent, 0.5 * height - 0.5 * ydescent
        p = RegularPolygon(xy=center, numVertices = 4, radius = 10, orientation=np.radians(45))
        self.update_prop(p, orig_handle, legend)
        p.set_transform(trans)
        return [p]
class HandlerCircle(HandlerPatch):
    def create_artists(self, legend, orig_handle,
                       xdescent, ydescent, width, height, fontsize, trans):
        center = 0.5 * width - 0.5 * xdescent, 0.5 * height - 0.5 * ydescent
        p = RegularPolygon(xy=center, numVertices = 100, radius = 10, orientation=0)
        self.update_prop(p, orig_handle, legend)
        p.set_transform(trans)
        return [p]

# To add the channel type legend to the plot
# axes: the plt.Axes object with the plot
# hb_type: the type of the board ("LD" for low density or "HD" for high density)
def add_channel_legend(axes, hb_type = "LD"):
    hexagon = RegularPolygon((0.5, 0.5), numVertices = 6, radius = 10, orientation = 0, edgecolor = 'k')
    pentagon = RegularPolygon((0.5, 0.5), numVertices = 5, radius = 10, orientation = 0)
    square = RegularPolygon((0.5, 0.5), numVertices = 4, radius = 10, orientation = np.radians(45))
    circle = RegularPolygon((0.5, 0.5), numVertices = 100, radius = 10, orientation = 0)
    if hb_type == "LD":
        handles = [hexagon, pentagon, square, circle]
        labels = ['calib', 'CM0', 'CM1', 'NC']
    elif hb_type == "HD":
        handles = [hexagon, pentagon, square]
        labels = ['calib', 'CM0', 'CM1']
    
    patch_legend = axes.legend(handles, labels, loc = 'lower right', fontsize = 'small',
        handler_map={hexagon: HandlerHexagon(), pentagon: HandlerPentagon(),
                            square: HandlerSquare(), circle: HandlerCircle()})
    axes.add_artist(patch_legend)

# To mark asic (chip) places on the plot
# axes: the plt.Axes object with the plot
# hb_type: the type of the board ("LD" for low density or "HD" for high density)
def ad_chip_geo(ax, hb_type = "LD"):
    if hb_type == "LD":
        #########################
        # LD board geometry and
        #    chip positions
        #         ______
        #        /  0  /\
        #       /_____/ 1\
        #       \  2  \  /
        #        \_____\/
        #
        ##########################

        # endpoints of line dividing chips 0 and 1
        x_01 = [0., 3.]     
        y_01 = [0., 5.]

        # endpoints of line dividing chips 0 and 2
        x_02 = [-5.5, 0.]
        y_02 = [0., 0.]

        # endpoints of line dividing chips 1 and 2
        x_12 = [0., 3.]     
        y_12 = [0., -5.6]

        # list of divider lines' endpoints
        line_co = [(x_01, y_01), (x_02, y_02), (x_12, y_12)]

        # marker posisition, angle and annotation position, angle for chip0
        chip0_pos = (-1.655, 2.25)      
        chip0_angle = 29.
        chip0_anno_pos = (-4.9, 2.8)    
        chip0_anno_angle = 63

        # marker posisition, angle and annotation position, angle for chip1
        chip1_pos = (3.4, -0.9)
        chip1_angle = 90.
        chip1_anno_pos = (4.15, 2.6)
        chip1_anno_angle = -58

        # marker posisition, angle and annotation position, angle for chip2
        chip2_pos = (-2.25, -2.8)
        chip2_angle = -31
        chip2_anno_pos = (-0.7, -5.95)
        chip2_anno_angle = 0.0

        # lists of chip positions, angles and annotation positions, angles
        chip_pos = [chip0_pos, chip1_pos, chip2_pos]
        chip_angles = [chip0_angle, chip1_angle, chip2_angle]
        chip_anno_pos = [chip0_anno_pos, chip1_anno_pos, chip2_anno_pos]
        chip_anno_angles = [chip0_anno_angle, chip1_anno_angle, chip2_anno_angle]

        # list of chip labels
        chip_labels = ['chip0', 'chip1', 'chip2']

        # chip marker width
        width = 0.9

    elif hb_type == "HD":
        ########################
        # HD board geometry and
        #    chip positions
        #        ______
        #       / 0/ 1/\
        #      /__/__/\5\
        #      \__2__\4\/
        #       \__3__\/
        #
        #########################

        # endpoints of line dividing chips 1 and 4, 5
        x_145 = [0., 3.2]     
        y_145 = [0., 5.6]

        # endpoints of line dividing chips 2 and 0, 1
        x_201 = [-6.2, 0.]  
        y_201 = [0., 0.]

        # endpoints of line dividing chips 4 and 2, 3
        x_423 = [0., 3.]     
        y_423 = [0., -5.6]

        # endpoints of line dividing chips 0 and 1
        x_01 = [-3.1, 0.] 
        y_01 = [0., 5.6]

        # endpoints of line dividing chips 2 and 3
        x_23 = [-4.8, 1.5] 
        y_23 = [-2.9, -2.9]

        # endpoints of line dividing chips 4 and 5
        x_45 = [1.6, 4.8] 
        y_45 = [2.5, -3.1]

        # list of divider lines' endpoints
        line_co = [(x_145, y_145), (x_201, y_201), (x_423, y_423), (x_01, y_01), (x_23, y_23), (x_45, y_45)]

        # marker posisition, angle and annotation position, angle for chip0
        chip0_pos = (-3.2, 2.1)      
        chip0_angle = 60.
        chip0_anno_pos = (-1.9, 5.8)    
        chip0_anno_angle = 0.

        # marker posisition, angle and annotation position, angle for chip1
        chip1_pos = (0., 2.1)      
        chip1_angle = 60.
        chip1_anno_pos = (1.2, 5.8)    
        chip1_anno_angle = 0.

        # marker posisition, angle and annotation position, angle for chip2
        chip2_pos = (-3.5, -1.6)      
        chip2_angle = 0.
        chip2_anno_pos = (-6.2, -2.1)    
        chip2_anno_angle = 120.

        # marker posisition, angle and annotation position, angle for chip3
        chip3_pos = (-2., -4.5)      
        chip3_angle = 0.
        chip3_anno_pos = (-4.55, -5.)    
        chip3_anno_angle = 120.

        # marker posisition, angle and annotation position, angle for chip4
        chip4_pos = (1.8, -1.05)      
        chip4_angle = -60.
        chip4_anno_pos = (3.8, -4.9)    
        chip4_anno_angle = -120.

        # marker posisition, angle and annotation position, angle for chip5
        chip5_pos = (3.4, 1.8)      
        chip5_angle = -60.
        chip5_anno_pos = (5.4, -2.1)    
        chip5_anno_angle = -120.

        # lists of chip positions, angles and annotation positions, angles
        chip_pos = [chip0_pos, chip1_pos, chip2_pos, chip3_pos, chip4_pos, chip5_pos]
        chip_angles = [chip0_angle, chip1_angle, chip2_angle, chip3_angle, chip4_angle, chip5_angle]
        chip_anno_pos = [chip0_anno_pos, chip1_anno_pos, chip2_anno_pos, chip3_anno_pos, chip4_anno_pos, 
                                                                                            chip5_anno_pos]
        chip_anno_angles = [chip0_anno_angle, chip1_anno_angle, chip2_anno_angle, chip3_anno_angle, 
                                                                        chip4_anno_angle, chip5_anno_angle]

        # list of chip labels 
        chip_labels = ['chip0', 'chip1', 'chip2', 'chip3', 'chip4', 'chip5']

        # chip marker width
        width = 1.3

    # divider line and chip marker, annotation color
    color = 'black'

    # plot the divider lines
    for co in line_co:
        x, y = co
        ax.plot(x, y, linestyle = 'dashed', linewidth = 4., color = color, alpha = 0.5)

    # plot the chip markers and annotation
    for chip_xy, chip_angle, chip_label, text_pos, text_angle in zip(chip_pos, chip_angles, 
                                                                    chip_labels, chip_anno_pos, chip_anno_angles):
        ax.add_patch(Rectangle(chip_xy, width = width, height = 0.5, 
                    angle = chip_angle, fill = False, linewidth = 2, alpha = 0.8, color = color))
        ax.annotate(chip_label, text_pos, rotation = text_angle, fontsize = 18, alpha = 1., color = color)

    # create legend for chip position and add to plot
    chip_legend_handle = [Rectangle((0.,0.), width = 0.9, height = 0.6, fill = False, color = color, alpha = 1.)]
    chip_legend_label = ['chip position']
    chip_legend = ax.legend(chip_legend_handle, chip_legend_label, loc = 'upper left', fontsize = 'small')
    if len(chip_pos) != 0:
        ax.add_artist(chip_legend)

# To plot the ADC graphs from a pandas dataFrame containing the data
# # df: pandas DataFrame with the data
# figdir: the output directory for the plots
# hb_type: the type of the board ("LD" for low density or "HD" for high density)
# label: a label to put in the plot names
def plot_hexmaps(df, figdir = "./", hb_type = "LD", label = None, module = "module812"):
    print("Plotting hexmaps")
    df_data = pd.DataFrame.from_dict(df[module]) # create clone to avoid conflict

    cmap = 'viridis' # select colormap

    # create the masks
    norm_mask = df_data["Channeltype"] == 0
    norm_mask &= df_data["Pad"] > 0 

    calib_mask = df_data["Channeltype"] == 1

    cm0_mask = df_data["Channeltype"] == 100
    cm0_mask &= pd.Series(df_data["Channel"]) % 2 == 0

    cm1_mask = df_data["Channeltype"] == 100 
    cm1_mask &= pd.Series(df_data["Channel"]) % 2 == 1 

    nc_mask = df_data["Channeltype"] == 0
    nc_mask &= df_data["Pad"] < 0

    masks = [norm_mask, calib_mask, cm0_mask, cm1_mask, nc_mask]
    data_types = ['norm', 'calib', 'cm0', 'cm1', 'nc']

    cycles = ["OGP", "0 Cycles", "1 Cycle", "2 Cycles", "3 Cycles", "Remount", "4 Cycles", "5 Cycles", "6 Cycles"]
    if "module800" in module: cycles = ["0 Cycles", "1 Cycle", "2 Cycles", "3 Cycles", "4 Cycles", "5 Cycles", "10 Cycles", "After Fix", "11 Cycles", "15 Cycles"]
    if args.testType != "": cycles = ["OGP"]

    for i, cycle in enumerate(cycles):
        for column in df_data.columns:
            if "Height" not in column: continue
            
            patches = []
            colors = np.array([])
            
            for mask, data_type in zip(masks, data_types):
                local_mask = mask.copy()
                #local_mask &= df_data[column] >= 0
                local_mask &= df_data["Cycle"] == cycle
                patches += create_patches(df_data, local_mask, data_type, hb_type = hb_type)
                colors = np.concatenate((colors, df_data[local_mask][column].values))
                
            patch_col = PatchCollection(patches, cmap = cmap, match_original = True)
            patch_col.set_array(colors)
            
            fig, ax = plt.subplots(figsize = (16,12))
            
            ax.add_collection(patch_col)
            ax.set_xlim([-7.274, +7.274])
            ax.set_ylim([-7.09, +7.09])

            diff = "1"
            if "OGP" in module: diff = "{OGP}"
            if i == 0 and "module812" in module: first = "OGP"
            if "module800" in module: first = str(i)
            else: first = str(i - 1)
            cb = plt.colorbar(patch_col)
            if "Diff" in module: cb.set_label(label = r"$\Delta(H_{" + first + "} - H_" + diff + ") [mm]$", size='large')
            else: cb.set_label(label = "Heights [mm]", size='large')

            # annotate chip positions on plot
            ad_chip_geo(ax, hb_type = hb_type)

            # add the legend
            add_channel_legend(ax, hb_type = hb_type)

            # add the title
            plt.title(label)
            plt.tight_layout()

            # save the figure
            figname = figdir + str(module) + "_" + column + "_" + cycle.replace(" ", "") + ".png"
            print(figname)
            plt.savefig(figname)
    return 1

##### Main functions: read ROOT file, decode to pandas and pass to plotting

# To make the hexmap plots from summary file
# fname: summary file name (relative path) that contains the data
# figdir: the output directory for the plots
# hb_type: the type of the board ("LD" for low density or "HD" for high density)
# label: a label to put in the plot names
def make_hexmap_plots_from_file(fname, figdir = "./", hb_type = "LD", label = None, module = ""):
    # fix label
    if label == None:
            label = os.path.basename(fname)
            label = label[:-5]

    # fix figdir
    if figdir == None:
        figdir = os.path.dirname(fname)
    if not figdir.endswith("/"):
        figdir += "/"
    
    print("Going to make plots for %s board from summary file %s into %s using label %s" %(hb_type, fname, figdir, label  ))

    df_data = pd.read_json(fname, typ = 'series')

    df_data = add_mapping(df_data, hb_type = hb_type, module = module)
    
    # do plots
    plot_hexmaps(df_data, figdir, hb_type, label, module)

    return 1

# simple function taking the dataFrame instead of filename to make the hexmap plots
# made for easier integration with pedestal_run_analysis
def make_hexmap_plots_from_df(df_data, figdir = "./", hb_type = "LD", label = None):
    # add mapping
    df_data = add_mapping(df_data, hb_type = hb_type)
    # do plots
    plot_hexmaps(df_data, figdir, hb_type, label)
    return 1

if __name__ == "__main__":

    parser = ArgumentParser()
    # parser arguments
    parser.add_argument("infname", type=str, help="Input summary file name")
    parser.add_argument("-d", "--figdir", type=str, default=None, help="Plot directory, if None (default), use same directory as input file")
    parser.add_argument("-t", "--hb_type", type=str, default="LD", help="Hexaboard type", choices=["LD","HD"])
    parser.add_argument("-l", "--label", type=str, default=None, help="Label to use in plots")
    parser.add_argument("-m", "--moduleName", type=str, default=None, help="Name of Module in JSON file")
    parser.add_argument("-p", "--testType", type=str, default="", help="Type of test that was run")

    args = parser.parse_args()
    jsonModule = os.path.basename(args.infname).replace(".json", "")
    make_hexmap_plots_from_file(args.infname, args.figdir, args.hb_type, args.label, jsonModule)
