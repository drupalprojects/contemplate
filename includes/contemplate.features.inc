<?php

/**
 * Implementation of hook_features_export_options().
 */
function contemplate_features_export_options() {
  $options = array();
  foreach(contemplate_get_templates() as $template) {
    if(strlen($template['type'])) {
      $options[$template['type']] = $template['type'];
    }     
  }
  
  return $options;
}

/**
 * Implementation of hook_features_export().
 */
function contemplate_features_export($data, &$export, $module_name = '') {

  $export['dependencies']['contemplate'] = 'contemplate';
  
  // Collect a module to preset map
  $map = features_get_default_map('contemplate');
  foreach ($data as $preset) {
    $export['features']['contemplate'][$preset] = $preset;
  }
}

/**
 * Implementation of hook_features_export_render().
 */
function contemplate_features_export_render($module_name, $data) {
  $items = array();
  foreach ($data as $key) {
    $template = contemplate_get_template($key);
    $items[$key] = $template;
  }
  $code = "  \$items = ". features_var_export($items, '  ') .";\n";
  $code .= '  return $items;';
  return array('contemplate_templates' => $code);
}

/**
 * Implementation of hook_features_revert().
 */
function contemplate_features_revert($module) {
  contemplate_features_rebuild($module);
}


function contemplate_features_rebuild($module) {
  if ($types = features_get_default('contemplate', $module)) {
    foreach($types as $type => $template) {
      
      // rework into the same format contemplate_save is used to
      $template['teaserfield'] = $template['teaser'];
      $template['bodyfield'] = $template['body'];
      $template['rssfield'] = $template['rss'];      
      $edit['values'] = $template;
      
      contemplate_save($edit);
    }
  }
}


function hook_contemplate_default_presets() {
  return array();
}
