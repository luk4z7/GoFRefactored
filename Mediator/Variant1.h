#pragma once

#include <list>

namespace MediatorPattern::Variant1
{
	class MouseEvent;

	class IWidget {};

	class DialogDirector {
	public:
		virtual ~DialogDirector() {}
		virtual void ShowDialog() {}
		virtual void WidgetChanged(IWidget*) = 0;
	protected:
		DialogDirector() {}
		virtual void CreateWidgets() = 0;
	};

	class Widget : public IWidget {
	public:
		Widget(DialogDirector*) {}
		virtual void Changed();
		virtual void HandleMouse(MouseEvent& event) {}
		// ... 
	private:
		DialogDirector* _director;
	};

	void Widget::Changed()
	{
		_director->WidgetChanged(this);
	}

	class ListBox : public Widget {
	public:
		ListBox(DialogDirector* d) : Widget(d) {}
		virtual const char* GetSelection() { return 0; }
		virtual void SetList(std::list<char*>* listItems) {}
		virtual void HandleMouse(MouseEvent& event) {}
		// ...  
	};

	class EntryField : public Widget {
	public:
		EntryField(DialogDirector* d) : Widget(d) {}
		virtual void SetText(const char* text) {}
		virtual const char* GetText() { return 0; }
		virtual void HandleMouse(MouseEvent& event) {}
		// ... 
	};

	class Button : public Widget {
	public:
		Button(DialogDirector* d) : Widget(d) {}
		virtual void SetText(const char* text) {}
		virtual void HandleMouse(MouseEvent& event);
		// ... 
	};

	void Button::HandleMouse(MouseEvent& event) {
		// ... 
		Changed();
	}

	class FontDialogDirector : public DialogDirector {
	public:
		FontDialogDirector() {}
		virtual ~FontDialogDirector() {}
		virtual void WidgetChanged(Widget*);
	protected:
		virtual void CreateWidgets();
	private:
		Button* _ok;
		Button* _cancel;
		ListBox* _fontList;
		EntryField* _fontName;
	};

	void FontDialogDirector::CreateWidgets() {
		_ok = new Button(this);
		_cancel = new Button(this);
		_fontList = new ListBox(this);
		_fontName = new EntryField(this);
		// fill the listBox with the available font names 
		// assemble the widgets in the dialog 
	}

	void FontDialogDirector::WidgetChanged(Widget* theChangedWidget) {
		if (theChangedWidget == _fontList) {
			_fontName->SetText(_fontList->GetSelection());
		}
		else if (theChangedWidget == _ok) {
			// apply font change and dismiss dialog 
			// ... 
		}
		else if (theChangedWidget == _cancel) {
			// dismiss dialog 
		}
	}

}
