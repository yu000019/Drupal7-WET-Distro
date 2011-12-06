<?php

/**
 * @file
 * Advanced migration examples. These serve two purposes:
 *
 */

/**
 * Class for XML Mult file.
 */
class XML_Web_Usability_GovMigration extends XMLMigration {

  public function __construct() {
    parent::__construct(MigrateGroup::getInstance('wetkit'));
    $this->description = t('XML Import of Documents for the Web Experience Toolkit');
    $this->team = array(
      new MigrateTeamMember('William Hearn', 'william.hearn@statcan.gc.ca', t('Administrator')),
    );
    $this->issuePattern = 'http://drupal.org/node/:id:';
    
    // There isn't a consistent way to automatically identify appropriate "fields"
    // from an XML feed, so we pass an explicit list of source fields
    $fields = array(
      'name' => t('Document name'),
      'description' => t('Description of document'),
      'authorid' => t('UID of the author'),
    );

    // The source ID here is the one retrieved from each data item in the XML file, and
    // used to identify specific items
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'sourceid' => array(
          'type' => 'varchar',
          'length' => 25,
          'not null' => TRUE,
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );
    
    // This can also be an URL instead of a file path.
    $xml_folder = DRUPAL_ROOT . '/' . drupal_get_path('module', 'wetkit_migrate') . '/xml/';
    $list_url = $xml_folder . 'index.xml';
    // Each ID retrieved from the list URL will be plugged into :id in the
    // item URL to fetch the specific objects.
    $item_url = $xml_folder . 'documents/' . ':id.xml';
    
    // We use the MigrateSourceList class for any source where we obtain the list
    // of IDs to process separately from the data for each item. The listing
    // and item are represented by separate classes, so for example we could
    // replace the XML listing with a file directory listing, or the XML item
    // with a JSON item.
    $this->source = new MigrateSourceList(new MigrateListXML($list_url),
      new MigrateItemXML($item_url), $fields);

    $this->destination = new MigrateDestinationNode('page', array('text_format' => 'full_html'));

    $this->addFieldMapping('title', 'name')
         ->xpath('name');
    $this->addFieldMapping('uid', 'authorid')
         ->xpath('authorid')
         ->defaultValue(1);
    $this->addFieldMapping('language', 'langcode')
         ->xpath('langcode');
    $this->addFieldMapping('status', 'status')
        ->defaultValue(1);
    $this->addFieldMapping('path', 'path')
        ->xpath('path');
    $this->addFieldMapping('body', 'description')
         ->xpath('description')
         ->arguments(array('format' => 'full_html'));
     $this->addFieldMapping('pathauto')
         ->defaultValue(FALSE);
  }
  
  public function postImport(){
    
    //Fix Translation ID
    $result = db_query("SELECT destid1 FROM {migrate_map_xml_web_usability_gov}");
    $currentRowCount = 0;
    $current_translateid = 0;
    //$translation_set_tsid = 0;
    foreach ($result as $record) {
      if ($currentRowCount % 2 == 0)
      {
        $node = node_load($record->destid1);
        $node->pathauto_perform_alias = FALSE;
        $node->tnid = $record->destid1;
        $current_translateid = $record->destid1;
        node_save($node);
      }
      else {
        $node = node_load($record->destid1);
        $node->pathauto_perform_alias = FALSE;
        $node->tnid = $current_translateid;
        node_save($node);
      }      
      $currentRowCount++;
    }
    
   _menulinks_generate('help', 'main-menu', 'Help');
   _menulinks_generate('help', 'main-menu', 'Aide');
   _menulinks_generate('contactus', 'main-menu', 'Contact Us');
   _menulinks_generate('contactus', 'main-menu', 'Nous Contacter');
   
   _menulinks_generate('terms', 'menu-goc-terms-bar', 'Terms and Conditions');
   _menulinks_generate('terms', 'menu-goc-terms-bar', 'Avis');
   _menulinks_generate('transparency', 'menu-goc-terms-bar', 'Transparency');
   _menulinks_generate('transparency', 'menu-goc-terms-bar', 'Transparence');
   
   _menulinks_generate('aboutus', 'menu-goc-about-us-bar', 'About Us');
   _menulinks_generate('aboutus', 'menu-goc-about-us-bar', 'À propos de nous');
   _menulinks_generate('mandate', 'menu-goc-about-us-bar', 'Our Mandate');
   _menulinks_generate('mandate', 'menu-goc-about-us-bar', 'Notre mandat');
   _menulinks_generate('minister', 'menu-goc-about-us-bar', 'Our Minister');
   _menulinks_generate('minister', 'menu-goc-about-us-bar', 'Le ministre');

   _menulinks_generate('contactus', 'menu-goc-contact-bar', 'Contact Us');
   _menulinks_generate('contactus', 'menu-goc-contact-bar', 'Contactez-nous');
   _menulinks_generate('find/employee', 'menu-goc-contact-bar', 'Find an Employee');
   _menulinks_generate('find/employee', 'menu-goc-contact-bar', 'Trouvez un(e) employé(e)');
   _menulinks_generate('contact/phone', 'menu-goc-contact-bar', 'Phone Numbers');
   _menulinks_generate('contact/phone', 'menu-goc-contact-bar', 'Numéros de téléphone');

   _menulinks_generate('news', 'menu-goc-news-bar', 'News');
   _menulinks_generate('news', 'menu-goc-news-bar', 'Média');
   _menulinks_generate('news/releases', 'menu-goc-news-bar', 'News Releases');
   _menulinks_generate('media/advisories', 'menu-goc-news-bar', 'Media Advisories');
   _menulinks_generate('multimedia', 'menu-goc-news-bar', 'Multimedia');
   _menulinks_generate('news/releases', 'menu-goc-news-bar', 'Communiqués');
   _menulinks_generate('media/advisories', 'menu-goc-news-bar', 'Avis aux médias');
   _menulinks_generate('multimedia', 'menu-goc-news-bar', 'News Releases');
   
   _menulinks_generate('connected', 'menu-goc-connected-bar', 'Stay Connected');
   _menulinks_generate('connected', 'menu-goc-connected-bar', 'Restez branchés');   

   //Clears all menu caches
   menu_cache_clear_all();
  }
  
  public function postRollback() {
    
   _menulinks_generate('<front>', 'main-menu', 'Help');
   _menulinks_generate('<front>', 'main-menu', 'Aide');
   _menulinks_generate('<front>', 'main-menu', 'Contact Us');
   _menulinks_generate('<front>', 'main-menu', 'Nous Contacter'); 
   
   _menulinks_generate('<front>', 'menu-goc-terms-bar', 'Terms and Conditions');
   _menulinks_generate('<front>', 'menu-goc-terms-bar', 'Avis');
   _menulinks_generate('<front>', 'menu-goc-terms-bar', 'Transparency');
   _menulinks_generate('<front>', 'menu-goc-terms-bar', 'Transparence');
  
   _menulinks_generate('<front>', 'menu-goc-about-us-bar', 'About Us');
   _menulinks_generate('<front>', 'menu-goc-about-us-bar', 'À propos de nous');
   _menulinks_generate('<front>', 'menu-goc-about-us-bar', 'Our Mandate');
   _menulinks_generate('<front>', 'menu-goc-about-us-bar', 'Notre mandat');
   _menulinks_generate('<front>', 'menu-goc-about-us-bar', 'Our Minister');
   _menulinks_generate('<front>', 'menu-goc-about-us-bar', 'Le ministre');
   
   _menulinks_generate('<front>', 'menu-goc-contact-bar', 'Contact Us');
   _menulinks_generate('<front>', 'menu-goc-contact-bar', 'Contactez-nous');
   _menulinks_generate('<front>', 'menu-goc-contact-bar', 'Find an Employee');
   _menulinks_generate('<front>', 'menu-goc-contact-bar', 'Trouvez un(e) employé(e)');
   _menulinks_generate('<front>', 'menu-goc-contact-bar', 'Phone Numbers');
   _menulinks_generate('<front>', 'menu-goc-contact-bar', 'Numéros de téléphone');
   
   _menulinks_generate('<front>', 'menu-goc-news-bar', 'News');
   _menulinks_generate('<front>', 'menu-goc-news-bar', 'Média');
   _menulinks_generate('<front>', 'menu-goc-news-bar', 'News Releases');
   _menulinks_generate('<front>', 'menu-goc-news-bar', 'Media Advisories');
   _menulinks_generate('<front>', 'menu-goc-news-bar', 'Multimedia');
   _menulinks_generate('<front>', 'menu-goc-news-bar', 'Communiqués');
   _menulinks_generate('<front>', 'menu-goc-news-bar', 'Avis aux médias');
   _menulinks_generate('<front>', 'menu-goc-news-bar', 'News Releases');
   
   _menulinks_generate('<front>', 'menu-goc-connected-bar', 'Stay Connected');
   _menulinks_generate('<front>', 'menu-goc-connected-bar', 'Restez branchés'); 

    //Clears all menu caches
    menu_cache_clear_all();
  }
}
