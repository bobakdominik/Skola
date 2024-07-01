bl_info = {
    "name" : "Heart controller",
    "author" : "Dominik Bobak",
    "version" : (1, 2),
    "blender" : (4, 0, 1),
    "location" : "3D Viewport > Sidebar > Heart",
    "warning" : "Usable only with heart animation",
    "description" : "Custom side panel for controlling heart animation",
    "category" : "Animation"
}

import bpy

# Function for hiding objects in collection
def HA_hide_collection(collection_name):
    for child in bpy.data.collections[collection_name].objects:
        child.hide_set(True)

# Function for unhiding objects in collection
def HA_unhide_collection(collection_name):
    for child in bpy.data.collections[collection_name].objects:
        child.hide_set(False)

# Function for displaying selected graph
def HA_show_graphs(self, context):
    scene = context.scene
    ha_properties = scene.HA_properties_pointer
    graphName=""
    if ha_properties.ha_graph_enum == 'Graph_ECG':
        graphName="ECG"
    for myCol in bpy.data.collections['Graphs'].children:
        if myCol.name == graphName:
            HA_unhide_collection(myCol.name)
        else:
            HA_hide_collection(myCol.name)

# Function for setting animation speed      
def HA_set_animation_speed(self, context):
    multiplier = context.scene.HA_properties_pointer.ha_float_speed_multiplier
    speed = int(60*multiplier) 
    context.scene.render.fps = speed
    
# Function for toggle heart cover visibility
def HA_toggle_heart_cover_visibility(self, context):
    collectionName = "Heart_cover"
    scene = context.scene
    ha_properties = scene.HA_properties_pointer
    if ha_properties.ha_is_heart_interior_displayed:
        HA_hide_collection(collectionName)
    else:
        HA_unhide_collection(collectionName)

# Function for toggle blood visibility
def HA_toggle_blood_visibility(self, context):
    collectionName = "Blood"
    scene = context.scene
    ha_properties = scene.HA_properties_pointer
    if ha_properties.ha_is_blood_displayed:
        HA_unhide_collection(collectionName)
    else:
        HA_hide_collection(collectionName)

# Operator for reseting values
class HA_reset_default_values(bpy.types.Operator):
    bl_idname = "animation.ha_reset_default_values"
    bl_label = "Reset animation"
    def execute(self, context):
        bpy.data.scenes['Scene'].frame_end = 60
        bpy.context.scene.frame_set(1)
        bpy.context.scene.eevee.use_bloom = True
        bpy.context.scene.HA_properties_pointer.ha_float_speed_multiplier = 1
        bpy.context.scene.HA_properties_pointer.ha_graph_enum = 'Graph_none'
        bpy.context.scene.HA_properties_pointer.ha_is_heart_interior_displayed = False
        bpy.context.scene.HA_properties_pointer.ha_is_blood_displayed = False
        return {"FINISHED"}   
   
# Operator for reseting animation  
class HA_reset_animation(bpy.types.Operator):
    bl_idname = "animation.ha_reset_animation"
    bl_label = "Reset animation"
    def execute(self, context):
        scene = context.scene
        scene.frame_set(1)
        return {"FINISHED"}

# Class for properties    
class HA_properties(bpy.types.PropertyGroup):
    ha_graph_enum : bpy.props.EnumProperty(
        name = "Graph:",
        description = "Enumerator of graphs for heart animation",
        items = [
            ('Graph_none', "none", ""),
            ('Graph_ECG', "ECG", ""),
        ],
        default = 'Graph_none',
        update = HA_show_graphs
    )
    
    ha_float_speed_multiplier: bpy.props.FloatProperty(
        name = "Speed multiplier:", 
        description = "Float property for animation speed multiplier",
        default = 1.0, 
        min = 0.25, 
        max = 2.0,
        step = 25, 
        precision = 2,
        update = HA_set_animation_speed
    )
        
    ha_is_heart_interior_displayed: bpy.props.BoolProperty(
        name = "Heart Interior",
        description = "Boolean property for heart cover display check box",
        update = HA_toggle_heart_cover_visibility
    )
    
    ha_is_blood_displayed: bpy.props.BoolProperty(
        name = "Blood",
        description = "Boolean property for heart blood check box",
        update = HA_toggle_blood_visibility
    )


# Class for main panel
class VIEW3D_PT_HeartPanel(bpy.types.Panel):
    bl_label = "Heart Animation Control"
    bl_category = "Heart"
    bl_idname = "VIEW3D_PT_HeartPanel"
    bl_space_type = "VIEW_3D"
    bl_region_type = "UI"
    bl_options = {'HEADER_LAYOUT_EXPAND'}
    
    def draw(self, context):
        
        layout = self.layout
        scene = context.scene
        ha_properties = scene.HA_properties_pointer
        screen = context.screen
        
        layout.use_property_split = True
        layout.use_property_decorate = True
        
        layout.use_property_split = True
        flow = layout.grid_flow(row_major=False, columns=0, even_columns=True, even_rows=False, align=True)
        
        col = flow.column(heading="Display:")
        col.prop(ha_properties, "ha_is_heart_interior_displayed", text="Interior")
        col = flow.column()
        col.prop(ha_properties, "ha_is_blood_displayed", text="Blood")
        layout.use_property_split = False
        col = flow.column()
        col.prop(ha_properties, "ha_graph_enum")
        
        layout.use_property_decorate = False
        
        layout.row().separator()
        
        box = layout.box()
        row = box.row()
        row.label(text = "Heart Animation")
        row = box.row()
        row.label(text = "Speed Multiplier:")
        row.prop(ha_properties, "ha_float_speed_multiplier", text="")
        row = box.row()
        row.operator(HA_reset_animation.bl_idname, icon="REW", text="Reset")
        label = "Play" if not context.screen.is_animation_playing else "Stop"
        icon = "PLAY" if not context.screen.is_animation_playing else "PAUSE"
        row.operator("screen.animation_play", icon=icon, text=label)
        
        layout.row().separator()
        row = layout.row()
        row.operator(HA_reset_default_values.bl_idname,text="Reset Values")
        

classes = [HA_reset_default_values, HA_properties, VIEW3D_PT_HeartPanel, HA_reset_animation]
def register():
    for cls in classes:
        bpy.utils.register_class(cls)
    bpy.types.Scene.HA_properties_pointer = bpy.props.PointerProperty(type = HA_properties)
        
def unregister():
    for cls in classes:
        bpy.utils.unregister_class(cls)
    del bpy.types.Scene.HA_properties_pointer
    
if __name__ == "__main__":
    register()