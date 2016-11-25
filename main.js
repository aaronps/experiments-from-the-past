
function TranslationEngine()
{
    this.trans = {};
    this.default_language = [];
    this.languages = {};
    this.active_language = [];
}

TranslationEngine.prototype.addLanguage = function( lang_name, lang_data )
{
    this.languages[lang_name] = lang_data;
};

TranslationEngine.prototype.setDefaultLanguage = function( lang_name )
{
    this.default_language = lang_name;
};

TranslationEngine.prototype.split_language_regex = /[_-]/;

TranslationEngine.prototype.setActiveLanguage = function( lang_name )
{
    this.active_language = [ lang_name ];

    var sep = lang_name.split(this.split_language_regex);
    if ( sep.length > 1 )
    {
        this.active_language.push(sep[0]);
    }

    if ( this.active_language[this.active_language.length-1] != this.default_language )
	    this.active_language.push(this.default_language);

//    alert('active: ' + this.active_language.join());
//    this.active_language = lang_name;
/*    var lang = this.languages[lang_name];
    if ( lang != null )
    {
        var deflan = this.default_language;
        var trans = this.trans;
        for ( var t in deflan )
        {
            trans[t] = lang[t] || deflan[t]; // use the language or the default;
        }
    }
    */
};

TranslationEngine.prototype.translate = function( text, params )
{
    var tx = text;
    var transobj = this.trans[text];
    
    if ( transobj != null )
    {
        var ttext = null;
        for ( var t = 0, e=this.active_language.length; t<e; t++ )
        {
            ttext = transobj[this.active_language[t]];
            if ( ttext != null )
            {
                tx = ttext;
                break;
            }
        }
    }

    if ( params != null )
    {
        for ( var v in params )
        {
            tx = tx.replace( v, params[v] );
        }
    }
    
    return tx;
};

TranslationEngine.prototype.translateElement = function( element, params )
{
    var tdata = {};
    var text;
    var nodeName = element.nodeName.toLowerCase();
    if (  nodeName == 'input')
    {
        if ( element.type == 'button' || element.type == 'reset' || element.type == 'submit' )
        {
            text = element.value;
            tdata.value = {text:text, params:params};
            element.value = this.translate( text, params );
        }
    }
    else if ( nodeName == 'optgroup' )
    {
        text = element.label;
        tdata.label = {text:text, params:params};
        element.label = this.translate( text, params);
    }
    else
    {
        text = element.innerHTML;
        tdata.innerHTML = {text:text, params:params};
        element.innerHTML = this.translate( text, params );
    }

    if ( element.title != null )
    {
        text = element.title;
        tdata.title = {text:text, params:params};
        element.title = this.translate( text, params );
    }
    
    element._translation_engine_data = tdata;
    jQuery(element).addClass('translated_text');
    
};

TranslationEngine.prototype.retranslateDocument = function()
{
    var all_translatable_text = jQuery('.translated_text');
    for ( var n = 0; n < all_translatable_text.length; n++ )
    {
        var obj = all_translatable_text[n];
        if ( obj._translation_engine_data != null )
        {
            var tdata = obj._translation_engine_data;
            for ( var v in tdata )
                obj[v] = this.translate(tdata[v].text, tdata[v].params);
        }
    }
};

TranslationEngine.prototype.translateSimples = function( base_element )
{
    var all_translatable_text = jQuery('.translatable',base_element);
    for ( var n = 0; n < all_translatable_text.length; n++ )
    {
        var obj = all_translatable_text[n];
        if ( obj._translation_engine_data == null )
        {
            this.translateElement(obj, null);
        }
            
    }
};

TranslationEngine.prototype.translateSimplesTemplate = function( base_element )
{
    var all_translatable_text = jQuery('.translatable_tpl',base_element);
    all_translatable_text.addClass('translatable');
    this.translateSimples(base_element);
};

TranslationEngine.prototype.mergeTranslations = function ( to_merge )
{
	this.trans = to_merge;
};

TranslationEngine.prototype.setTextDirection = function ( direction )
{
    var orig_dir = document.body.dir;
    if ( orig_dir != direction )
    {
        document.body.dir = direction;
    }
}

var TE = null;

var Translations = {
     'Hello world':{
	en:'Hello @name\'s world @number'
       ,es:'Hola al mundo @number de @name'
       ,zh_CN:'你好@name的世界@number号'
       ,arabe:'مرحبا@name العالم @number'
     }
    ,'Bye world':{
	en:'Bye @name\'s world @number'
       ,es:'Adios al mundo @number de @name'
       ,zh_CN:'再见@name的世界@number号'
       ,arabe:'وداعا@name العالم @number'
     }
    ,'Center':{
	en_GB:'Centre'
       ,es:'Centro'
       ,zh_CN:'中'
       ,arabe:'مركز'
     }
    ,'Time to go':{
	en:'Time to go in American english (without the thing)'
       ,en_GB:'Time to go in British English'
       ,es:'Hora the irse'
       // zh_CN not translated, should use default text
       ,arabe:'الوقت للذهاب'
     }
    ,'trans_button':{
	en:'Some nice button'
       ,es:'Un bonito boton'
       ,zh_CN:'好看的Button'
       ,arabe:'زر بعض لطيفة'
     }
    ,'First':{
	en:'First'
       ,es:'Primero'
       ,zh_CN:'第一'
       ,arabe:'الأول'
     }
    ,'Second':{
	en:'Second'
       ,es:'Segundo'
       ,zh_CN:'第二'
       ,arabe:'الثانية'
     }
    ,'Thirth':{
	en:'Third'
       ,es:'Tercero'
       ,zh_CN:'第三'
       ,arabe:'الثالثة'
     }
    ,'group1':{
	en:'First Group'
       ,es:'Primer grupo'
       ,zh_CN:'第一组'
       ,arabe:'المجموعة الأولى'
     }
    ,'group2':{
	en:'Second Group'
       ,es:'Segundo grupo'
       ,zh_CN:'第二组'
       ,arabe:'المجموعة الثانية'
     }

};

function init()
{
    TE = new TranslationEngine();

    TE.mergeTranslations(Translations);

    TE.setDefaultLanguage('en');
    TE.setActiveLanguage('en');
    
    TE.translateSimples();
    
    TE.translateElement( document.getElementById('some_text'), {'@name':'Tiantian','@number':20});
    TE.translateElement( document.getElementById('some_more_text'), {'@name':'Aaron','@number':21});
    
}


function set_english()
{
    TE.setActiveLanguage('en');
    TE.setTextDirection('ltr');
    TE.retranslateDocument();
}

function set_englishgb()
{
    TE.setActiveLanguage('en_GB');
    TE.setTextDirection('ltr');
    TE.retranslateDocument();
}

function set_spanish()
{
    TE.setActiveLanguage('es');
    TE.setTextDirection('ltr');
    TE.retranslateDocument();
}

function set_zh_CN()
{
    TE.setActiveLanguage('zh_CN');
    TE.setTextDirection('ltr');
    TE.retranslateDocument();
}

function set_arabe()
{
    TE.setActiveLanguage('arabe');
    TE.setTextDirection('rtl');
    TE.retranslateDocument();
}
