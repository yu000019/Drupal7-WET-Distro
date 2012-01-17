<?php
/**
 * @file
 * wetkit_workflow_rules.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function wetkit_workflow_rules_default_rules_configuration() {
  $items = array();
  $items['rules_publish_workflow'] = entity_import('rules_config', '{ "rules_publish_workflow" : {
      "LABEL" : "Send Email(s) on Workbench Moderation Transition (Drafts -\\u003e Needs Review)",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Workflow" ],
      "REQUIRES" : [ "workbench_moderation", "rules" ],
      "ON" : [ "workbench_moderation_after_moderation_transition" ],
      "IF" : [
        { "contents_current_state" : { "node" : [ "node" ], "moderation_state" : "needs_review" } }
      ],
      "DO" : [
        { "mail" : {
            "to" : "[site:mail]",
            "subject" : "Sample Title",
            "message" : "Sample Body Message"
          }
        }
      ]
    }
  }');
  $items['rules_rules_publish_workflow2'] = entity_import('rules_config', '{ "rules_rules_publish_workflow2" : {
      "LABEL" : "Send Email(s) on Workbench Moderation Transition (Needs Review -\\u003e Published)",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Workflow" ],
      "REQUIRES" : [ "workbench_moderation", "rules" ],
      "ON" : [ "workbench_moderation_after_moderation_transition" ],
      "IF" : [
        { "contents_current_state" : { "node" : [ "node" ], "moderation_state" : "published" } }
      ],
      "DO" : [
        { "mail" : {
            "to" : "[site:mail]",
            "subject" : "Sample Title",
            "message" : "Sample Body Message"
          }
        }
      ]
    }
  }');
  $items['rules_scheduler_content_to_be_published'] = entity_import('rules_config', '{ "rules_scheduler_content_to_be_published" : {
      "LABEL" : "Scheduler: Content to be published",
      "PLUGIN" : "rule",
      "TAGS" : [ "scheduler" ],
      "REQUIRES" : [ "workbench_moderation" ],
      "USES VARIABLES" : { "scheduler_node" : { "label" : "Scheduler: Node", "type" : "node", "parameter" : false } },
      "IF" : [
        { "contents_current_state" : { "node" : [ "scheduler-node" ], "moderation_state" : "needs_review" } }
      ],
      "DO" : [
        { "workbench_moderation_set_state" : { "node" : [ "scheduler-node" ], "moderation_state" : "published" } }
      ],
      "PROVIDES VARIABLES" : [ "scheduler_node" ]
    }
  }');
  return $items;
}
