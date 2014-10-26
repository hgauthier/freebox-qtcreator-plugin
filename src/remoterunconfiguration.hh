/*
  Freebox QtCreator plugin for QML application development.

  This library is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2.1 of the
  License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not see
  http://www.gnu.org/licenses/lgpl-2.1.html.

  Copyright (c) 2014, Freebox SAS, See AUTHORS for details.
*/
#ifndef FREEBOXRUNCONFIGURATION_HH_
# define FREEBOXRUNCONFIGURATION_HH_

#include <projectexplorer/localapplicationrunconfiguration.h>

namespace Freebox {

namespace Internal {
    class RunConfigurationFactory;
}

class RemoteRunConfiguration : public ProjectExplorer::RunConfiguration
{
    Q_OBJECT

    friend class Internal::RunConfigurationFactory;
    friend class Project; // to call updateEnabled()

public:
    RemoteRunConfiguration(ProjectExplorer::Target *parent, Core::Id id);

    QWidget *createConfigurationWidget();
    QString workingDirectory() const;
    QString commandLineArguments() const;

    enum MainScriptSource {
        FileInEditor,
        FileInProjectFile,
        FileInSettings
    };
    MainScriptSource mainScriptSource() const;
    void setScriptSource(MainScriptSource source,
                         const QString &settingsPath = QString());
    QString mainScript() const;

signals:
    void scriptSourceChanged();

protected:
    RemoteRunConfiguration(ProjectExplorer::Target *parent,
                           RemoteRunConfiguration *source);

    virtual bool fromMap(const QVariantMap &map);
    void setEnabled(bool value);

private slots:
    void updateEnabled();

private:
    QString m_currentFileFilename;
    QString m_mainScriptFilename;
    QString m_scriptFile;
    QString m_qmlViewerArgs;
    bool m_isEnabled;

    void ctor();
};

}

#endif /* !FREEBOXRUNCONFIGURATION_HH_ */