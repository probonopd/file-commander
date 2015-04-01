#include "cfinddialog.h"
#include "ui_cfinddialog.h"
#include "settings/csettings.h"

#define SETTINGS_SEARCH_EXPRESSION "Plugins/TextViewer/Expression"

#define SETTINGS_REGEX             "Plugins/TextViewer/Regex"
#define SETTINGS_BACKWARDS         "Plugins/TextViewer/SearchBackwards"
#define SETTINGS_CASE_SENSITIVE    "Plugins/TextViewer/CaseSensitive"
#define SETTINGS_WHOLE_WORDS       "Plugins/TextViewer/WholeWords"

CFindDialog::CFindDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CFindDialog)
{
	ui->setupUi(this);

	connect(ui->_btnCancel, SIGNAL(clicked()), SLOT(reject()));
	connect(ui->_btnFind, SIGNAL(clicked()), SLOT(accept()));
	connect(ui->_btnFind, SIGNAL(clicked()), SIGNAL(find()));
	connect(ui->_btnFindNext, SIGNAL(clicked()), SIGNAL(findNext()));

	auto s = CSettings::instance();
	ui->_searchText->setText(s->value(SETTINGS_SEARCH_EXPRESSION).toString());
	ui->_cbSearchBackwards->setChecked(s->value(SETTINGS_BACKWARDS).toBool());
	ui->_cbCaseSensitive->setChecked(s->value(SETTINGS_CASE_SENSITIVE).toBool());
	ui->_cbRegex->setChecked(s->value(SETTINGS_REGEX).toBool());
	ui->_cbWholeWords->setChecked(s->value(SETTINGS_WHOLE_WORDS).toBool());

#if QT_VERSION < QT_VERSION_CHECK(5,3,0)
	ui->_cbRegex->setVisible(false);
#endif
}

CFindDialog::~CFindDialog()
{
	saveSearchSettings();
	delete ui;
}

QString CFindDialog::searchExpression() const
{
	return ui->_searchText->text();
}

bool CFindDialog::regex() const
{
	return ui->_cbRegex->isChecked();
}

bool CFindDialog::searchBackwards() const
{
	return ui->_cbSearchBackwards->isChecked();
}

bool CFindDialog::wholeWords() const
{
	return ui->_cbWholeWords->isChecked();
}

bool CFindDialog::caseSensitive() const
{
	return ui->_cbCaseSensitive->isChecked();
}

void CFindDialog::accept()
{
	QDialog::accept();
	saveSearchSettings();
}

void CFindDialog::saveSearchSettings() const
{
	auto s = CSettings::instance();
	s->setValue(SETTINGS_SEARCH_EXPRESSION, searchExpression());
	s->setValue(SETTINGS_BACKWARDS, searchBackwards());
	s->setValue(SETTINGS_CASE_SENSITIVE, caseSensitive());
	s->setValue(SETTINGS_REGEX, regex());
	s->setValue(SETTINGS_WHOLE_WORDS, wholeWords());
}
